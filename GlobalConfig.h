#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

#include <FastLED.h>

struct DeviceConfig {
  short ledMode = 0;
  bool ledStatus = true;
  bool isNightModeOn = false;
  bool warning = false;
  bool warningStatus = true;
  uint8_t brightness = 255;
  uint8_t nightModeBrighness = 4;
  CRGB ledsColor = CRGB(0, 255, 0);
  CRGB gradientColor = CRGB(255, 0, 0);
};

extern DeviceConfig cfg;

#endif