import pyaudiowpatch as pyaudio
import numpy as np
import asyncio
import websockets
import httpx
import keyboard

# Set here your ESP32 IPs
ESP_IPS = ["10.0.1.18", "10.0.1.20", "10.0.1.21"]
CHUNK = 1024
sensitivity_divider = 500 
# ---------------------

async def set_esp_mode(ip, mode):
    url = f"http://{ip}/set?mode={mode}"
    try:
        async with httpx.AsyncClient() as client:
            print(f"-> Mode {mode} dla {ip}")
            await client.get(url, timeout=1.0)
    except Exception as e:
        print(f"X Błąd HTTP {ip}: {e}")

async def monitor_keyboard():
    """Zmienia czułość dynamicznie za pomocą klawiszy + i -"""
    global sensitivity_divider
    print(f"Sterowanie: [+] więcej LED, [-] mniej LED. Aktualna czułość: {sensitivity_divider}")
    
    while True:
        if keyboard.is_pressed('+') or keyboard.is_pressed('='):
            sensitivity_divider = max(100, sensitivity_divider - 100)
            print(f"*** Czułość zwiększona! Dzielnik: {sensitivity_divider} ***")
            await asyncio.sleep(0.2) # Debounce
        
        if keyboard.is_pressed('-'):
            sensitivity_divider = min(5000, sensitivity_divider + 100)
            print(f"*** Czułość zmniejszona! Dzielnik: {sensitivity_divider} ***")
            await asyncio.sleep(0.2) # Debounce
            
        await asyncio.sleep(0.05)

async def send_to_esp(ip, queue):
    await set_esp_mode(ip, 5)
    uri = f"ws://{ip}:81"
    try:
        while True:
            try:
                async with websockets.connect(uri) as websocket:
                    print(f"V Połączono WS: {ip}")
                    while True:
                        level = await queue.get()
                        await websocket.send(str(level))
                        queue.task_done()
            except (websockets.ConnectionClosed, OSError):
                await asyncio.sleep(2)
    except asyncio.CancelledError:
        await set_esp_mode(ip, 0)
        raise

async def capture_audio(queues):
    global sensitivity_divider
    p = pyaudio.PyAudio()
    
    try:
        wasapi_info = p.get_host_api_info_by_type(pyaudio.paWASAPI)
        default_device = p.get_device_info_by_index(wasapi_info["defaultOutputDevice"])
        
        loopback_dev = None
        for i in range(p.get_device_count()):
            dev = p.get_device_info_by_index(i)
            if dev["isLoopbackDevice"] and default_device["name"] in dev["name"]:
                loopback_dev = dev
                break

        if not loopback_dev:
            loopback_dev = default_device

        print(f"### Przechwytywanie z: {loopback_dev['name']} ###")

        stream = p.open(format=pyaudio.paInt16,
                        channels=loopback_dev["maxInputChannels"],
                        rate=int(loopback_dev["defaultSampleRate"]),
                        input=True,
                        input_device_index=loopback_dev["index"],
                        frames_per_buffer=CHUNK)

        while True:
            data = stream.read(CHUNK, exception_on_overflow=False)
            audio_data = np.frombuffer(data, dtype=np.int16).astype(np.float32)
            
            if len(audio_data) > 0:
                rms = np.sqrt(np.mean(audio_data**2))
                level = int(np.clip(rms / sensitivity_divider * 255, 0, 255))
                
                for q in queues:
                    if q.full(): q.get_nowait()
                    q.put_nowait(level)
            
            await asyncio.sleep(0.01)

    except asyncio.CancelledError:
        stream.stop_stream()
        stream.close()
        p.terminate()
        raise

async def main():
    queues = [asyncio.Queue(maxsize=1) for _ in ESP_IPS]
    
    tasks = [
        asyncio.create_task(capture_audio(queues)),
        asyncio.create_task(monitor_keyboard())
    ]
    
    for i, ip in enumerate(ESP_IPS):
        tasks.append(asyncio.create_task(send_to_esp(ip, queues[i])))
    
    try:
        await asyncio.gather(*tasks)
    except asyncio.CancelledError:
        pass
    finally:
        for task in tasks: task.cancel()
        await asyncio.gather(*tasks, return_exceptions=True)

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nZamykanie i przywracanie mode=0...")