#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <FastLED.h>

#include "GlobalConfig.h"
#include "webConfig.h"
#include "lightEffects.h"
#include "PIR.h"
#include "webSocketHandler.h"
#include "httpRequestHandler.h" 

const uint16_t NUM_LEDS = 108; //+11 //set how many LEDs you have
#define DATA_PIN 18            //set pin where data pin is connected
#define PIR_PIN 23             //set pin where PIR sensor is connected

// Important!!! uncomment lines below
// #define WIFI_SSID "SSID" //set your wifi ssid
// #define WIFI_PASSWORD "PASSWORD" //set your wifi password

DeviceConfig cfg;
AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
CRGB leds[NUM_LEDS];
PIR pir(PIR_PIN);

void setup() {
  Serial.begin(115200);
  cfg.load();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pir.setEnable(cfg.pirEnabled);
  pir.setDelay(cfg.pirDelay);

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  registerHttpHandlers();

  server.begin();
}

void loop() {
  if (cfg.ledStatus) {
    if (cfg.isNightModeOn)
      FastLED.setBrightness(cfg.nightModeBrighness);
    else
      FastLED.setBrightness(cfg.brightness);

    if (cfg.warning) {
      cfg.warning = catchWarning(3, 250);
    } else {
      switch (cfg.ledMode) {
        case 0: rainbowARGB(50); break;
        case 1: rainbowRGB(10); break;
        case 2: setColor(); break;
        case 3: thunder(250); break;
        case 4: gradient(100); break;
        case 5: webSocket.loop(); break;
        default: FastLED.clear();
      }
    }
  } else if (pir.isTriggered()) {
    pir.start();
  } else {
    FastLED.setBrightness(0);
  }

  FastLED.show();
  pir.update();
}