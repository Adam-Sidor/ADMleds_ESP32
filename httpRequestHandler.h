#ifndef HTTP_REQUEST_HANDLER_H
#define HTTP_REQUEST_HANDLER_H

#include <ESPAsyncWebServer.h>
#include "GlobalConfig.h"
#include "htmlResponse.h"
#include "PIR.h"

extern DeviceConfig cfg;
extern AsyncWebServer server;
extern PIR pir;

void registerHttpHandlers() {

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", getHTMLResponse());
  });

  server.on("/status", HTTP_GET, [&cfg](AsyncWebServerRequest *request) {
    request->send(200, "application/json", getStatusJSON(cfg));
  });

  server.on("/set", HTTP_GET, [&cfg, &pir](AsyncWebServerRequest *request) {
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

}

#endif