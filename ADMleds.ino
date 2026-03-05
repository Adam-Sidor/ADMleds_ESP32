#include <WiFi.h>
#include <FastLED.h>
#include <WebSocketsServer.h>
#include "GlobalConfig.h"
#include "webConfig.h"
#include "htmlResponse.h"
#include "lightEffects.h"
#include "PIR.h"
#include "webSocketHandler.h"

const uint16_t NUM_LEDS = 108;  //+11 //set how many LEDs you have
#define DATA_PIN 18             //set pin where data pin is connected
#define PIR_PIN 23              //set pin where PIR sensor is connected

// Important!!! uncomment lines below
// #define WIFI_SSID "SSID" //set your wifi ssid
// #define WIFI_PASSWORD "PASSWORD" //set your wifi password

DeviceConfig cfg;

WiFiServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
CRGB leds[NUM_LEDS];

PIR pir(PIR_PIN);

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  //set your WiFi settings
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(10);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  server.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pir.setDelay(5);
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop() {
  HTTPRecive();
  if (cfg.ledStatus) {
    if (cfg.isNightModeOn)
      FastLED.setBrightness(cfg.nightModeBrighness);
    else
      FastLED.setBrightness(cfg.brightness);

    if (cfg.warning) {
      cfg.warning = catchWarning(3, 250);
    } else {
      switch (cfg.ledMode) {
        case 0:
          rainbowARGB(50);
          break;
        case 1:
          rainbowRGB(10);
          break;
        case 2:
          setColor();
          break;
        case 3:
          thunder(250);
          break;
        case 4:
          gradient(100);
          break;
        case 5:
          webSocket.loop();
          break;
        default:
          FastLED.clear();
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

void HTTPRecive() {
  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";
    bool doonce = 1;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            sendHTMLResponse(client);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.indexOf("GET /status ") != -1) {
          sendStatusJSON(client, cfg); // Zaktualizowane wywołanie
          doonce = 0;
          break;
        }
        if (currentLine.indexOf("/mode=") != -1) {
          cfg.ledMode = catchValue("/mode=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/status=") != -1) {
          cfg.ledStatus = catchValue("/status=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/brightness=") != -1) {
          cfg.brightness = catchValue("/brightness=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/nightmode=") != -1) {
          cfg.isNightModeOn = catchValue("/nightmode=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/nightbrightness=") != -1) {
          cfg.nightModeBrighness = catchValue("/nightbrightness=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/r=") != -1) {
          cfg.ledsColor.r = catchValue("/r=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/g=") != -1) {
          cfg.ledsColor.g = catchValue("/g=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/b=") != -1) {
          cfg.ledsColor.b = catchValue("/b=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/gradientr=") != -1) {
          cfg.gradientColor.r = catchValue("/gradientr=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/gradientg=") != -1) {
          cfg.gradientColor.g = catchValue("/gradientg=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/gradientb=") != -1) {
          cfg.gradientColor.b = catchValue("/gradientb=", currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/warning") != -1) {
          if (currentLine.indexOf("/warning=") != -1) {
            cfg.warningStatus = catchValue("/warning=", currentLine);
          } else {
            cfg.warning = cfg.ledStatus & cfg.warningStatus;
          }
          doonce = 0;
        }
        if (currentLine.indexOf("/pir") != -1) {
          if (currentLine.indexOf("/enable=") != -1) {
            pir.setEnable(catchValue("/enable=", currentLine));
            doonce = 0;
          }
          if (currentLine.indexOf("/delay=") != -1) {
            pir.setDelay(catchValue("/delay=", currentLine));
            doonce = 0;
          }
        }
      }
    }
    client.stop();
    if (doonce == 0) {
      doonce = 1;
    }
  }
}

int catchValue(String valName, String currentLine) {
  String inputValue = "-1";
  int where = currentLine.indexOf(valName);
  if (where != -1) {
    inputValue = currentLine.substring(where + valName.length(), currentLine.length());
  }
  if (inputValue != "")
    return inputValue.toInt();
  else
    return -1;
}