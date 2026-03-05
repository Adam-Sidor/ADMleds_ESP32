#include <FS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <FastLED.h>

#include "GlobalConfig.h"
#include "webConfig.h"
#include "htmlResponse.h"
#include "lightEffects.h"
#include "PIR.h"
#include "webSocketHandler.h"

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

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", getHTMLResponse());
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "application/json", getStatusJSON(cfg));
  });

  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request){
    bool needsSaving = false;
    
    if (request->hasParam("mode")) {
      cfg.ledMode = request->getParam("mode")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("status")) {
      cfg.ledStatus = request->getParam("status")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("brightness")) {
      cfg.brightness = request->getParam("brightness")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("nightmode")) {
      cfg.isNightModeOn = request->getParam("nightmode")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("nightbrightness")) {
      cfg.nightModeBrighness = request->getParam("nightbrightness")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("r")) {
      cfg.ledsColor.r = request->getParam("r")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("g")) {
      cfg.ledsColor.g = request->getParam("g")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("b")) {
      cfg.ledsColor.b = request->getParam("b")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("gradientr")) {
      cfg.gradientColor.r = request->getParam("gradientr")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("gradientg")) {
      cfg.gradientColor.g = request->getParam("gradientg")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("gradientb")) {
      cfg.gradientColor.b = request->getParam("gradientb")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("warning")) {
      cfg.warningStatus = request->getParam("warning")->value().toInt();
      needsSaving = true;
    }
    if (request->hasParam("pir_enable")) {
      cfg.pirEnabled = request->getParam("pir_enable")->value().toInt();
      pir.setEnable(cfg.pirEnabled);
      needsSaving = true;
    }
    if (request->hasParam("pir_delay")) {
      cfg.pirDelay = request->getParam("pir_delay")->value().toInt();
      pir.setDelay(cfg.pirDelay);
      needsSaving = true;
    }
    if (request->hasParam("trigger_warning")) {
      cfg.warning = cfg.ledStatus & cfg.warningStatus;
    }

    if (needsSaving) cfg.save();
    request->send(200, "text/plain", "OK");
  });

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