# ADM leds - ESP32
Kontroler LED WS2812B na podstawie ESP32 wykorzystujący zapytania HTTP do sterowania kontrolerem.

---

## Spis treści
1. [Opis projektu](#opis-projektu)  
2. [Wymagania](#wymagania)  
3. [Instalacja](#instalacja)  
4. [Użycie](#użycie)  
5. [Funkcjonalności](#funkcjonalności)  
6. [Licencja](#licencja)  
7. [Kontakt](#kontakt)  

---

## Opis projektu
- Projekt umożliwia sterowanie taśmą LED WS2812B za pomocą zapytań HTTP, wykorzystując moduł ESP32 jako jednostkę sterującą.
- ESP32 obsługuje komunikację WiFi, umożliwiając zdalne zarządzanie oświetleniem przy użyciu przeglądarki internetowej lub [aplikacji mobilnej](https://github.com/Adam-Sidor/ADMleds_IOS).
- W projekcie znajduje się kod dla ESP32 napisany w Arduino IDE, który interpretuje zapytania HTTP i odpowiednio steruje diodami LED na taśmie.
- Projekt może być wykorzystany jako element inteligentnego domu, dekoracji świetlnej, lub w celach edukacyjnych do nauki protokołów sieciowych i sterowania diodami ARGB.  

---

## Wymagania
- Hardware:
    - ESP-32
    - Taśma LED WS2812B
    - Połączenie Wi-Fi
    - Zasilacz 5V
- Oprogramowanie:
    - Arduino IDE (Tylko podczas instalacji)
    - Przeglądarka internetowa
- Opcjonalnie:
    - [Aplikacja na iOS](https://github.com/Adam-Sidor/ADMleds_IOS)
    - [Skrypt na PC](https://github.com/Adam-Sidor/ADMleds_PC)

---

## Instalacja
Instrukcja krok po kroku, jak skonfigurować i uruchomić projekt:  
1. Sklonowanie repozytorium:  
   ```bash
   git clone https://github.com/Adam-Sidor/ADMleds_ESP32
   ```
2. Wgranie kodu na ESP-32:  
    - Otwórz plik `.ino` w Arduino IDE. 
    - Zainstaluj potrzebne biblioteki. 
    - Ustaw odpowiednie wartości w pliku tj. 
        - ilość diod 
        - numer pinu sterującego 
        - SSID twojego Wi-Fi
        - hasło twojego Wi-Fi
    - Wybierz odpowiedni port COM oraz model ESP-32.  
    - Wgraj kod na płytkę.
    - Otwórz monitor portu szeregowego i sprawdź przypisany adres IP - UWAGA! adres może ulec zmianie jeśli nie wykona się kolejnego kroku.
3. Ustawienie statycznego adresu IP (Opcjonalne)
4. Podłączenie komponentów
    - Połącz masę wszystkich komponentów.
    - Połącz zasilanie `+5V` do ESP-32 oraz taśmy led.
    - Połącz pin danych taśmy do wybranego w punkcie 2. pinu na mikrokontrolerze.

---

## Użycie
1. Przeglądarka
    - W swojej przeglądarce wejdź na adres zapisany w kroku 2 [instalacji](#instalacja)
    - Teraz możesz sterować swoimi Ledami z przeglądarki uzywając gotowych przycisków na stronie.
    - Dla bardziej zaawansowanych można ręcznie zmieniać adresy podstron np. `adresIP/status=1` włączy Ledy.
2. Aplikacja
    - Dla wygody została zaprojektowana [aplikacja](https://github.com/Adam-Sidor/ADMleds_IOS) na system iOS.
3. Skrypt na PC
    - Jeśli chcesz żeby twoje ledy włączały się automatycznie po włączeniu komputera możesz użyć przygotowanego [skryptu](https://github.com/Adam-Sidor/ADMleds_PC).


---

## Funkcjonalności
- Hostowanie serwera HTTP do sterowania.
- Dedykowana [aplikacja](https://github.com/Adam-Sidor/ADMleds_IOS) na iOS pozwalająca na sterowanie kilkoma urzadzeniami jednocześnie.
- Dedykowany [skrypt](https://github.com/Adam-Sidor/ADMleds_PC) pozwalający na automatyczne włączanie ledów.
- Włączanie i wyłączanie Ledów.
- Ustawienie jasności.
- Wiele efektów
    - Tęcza ARGB
    - Tęcza RGB
    - Ustawienie stałego koloru
    - Burza
    - 2 kolorowy gradient
- Tryb nocny
    - Zmniejszenie jasności
    - Ustawienie jasności trybu nocnego

---

## Licencja
Wszystkie prawa zastrzeżone. Projekt został udostępniony wyłącznie w celach demonstracyjnych i edukacyjnych.  
- Możesz korzystać z tego projektu do użytku osobistego i edukacyjnego.  
- Wykorzystanie komercyjne lub redystrybucja projektu w całości lub w części wymaga wyraźnej pisemnej zgody autora.

---

## Kontakt
- Autor: Adam Sidor  
- E-mail: sidoadsi1@gmail.com  
- LinkedIn: [Mój profil](https://www.linkedin.com/in/adam-sidor-088a56341)  
