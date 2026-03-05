#ifndef WEB_SOCKET_HANDLER_H
#define WEB_SOCKET_HANDLER_H

#include <WebSocketsServer.h>
#include <FastLED.h>
#include "GlobalConfig.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;
extern DeviceConfig cfg;

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_TEXT) {
    int volume = atoi((char*)payload);
    int numLedsToLight = map(volume, 0, 255, 0, NUM_LEDS);

    FastLED.clear();
    for (int i = 0; i < numLedsToLight; i++) {
      uint8_t ratio = map(i, 0, NUM_LEDS - 1, 0, 255);
      leds[i] = blend(cfg.ledsColor, cfg.gradientColor, ratio);
    }
    FastLED.show();
  }
}

#endif