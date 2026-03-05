#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

#include <FastLED.h>
#include <Preferences.h>

struct DeviceConfig {
  short ledMode = 0;
  bool ledStatus = true;
  bool isNightModeOn = false;
  bool warning = false;
  bool warningStatus = true;
  uint8_t brightness = 255;
  uint8_t nightModeBrighness = 16;
  CRGB ledsColor = CRGB(0, 255, 0);
  CRGB gradientColor = CRGB(255, 0, 0);
  bool pirEnabled = true;
  unsigned int pirDelay = 5;

  void save() {
    Preferences prefs;
    prefs.begin("led-config", false);
    prefs.putShort("mode", ledMode);
    prefs.putBool("status", ledStatus);
    prefs.putBool("night", isNightModeOn);
    prefs.putBool("warnStat", warningStatus);
    prefs.putUChar("bright", brightness);
    prefs.putUChar("nBright", nightModeBrighness);
    prefs.putUInt("color", ledsColor.as_uint32_t());
    prefs.putUInt("grad", gradientColor.as_uint32_t());
    prefs.putBool("pirEn", pirEnabled);
    prefs.putUInt("pirDel", pirDelay);
    prefs.end();
  }

  void load() {
    Preferences prefs;
    prefs.begin("led-config", true);
    ledMode = prefs.getShort("mode", 0);
    ledStatus = prefs.getBool("status", true);
    isNightModeOn = prefs.getBool("night", false);
    warningStatus = prefs.getBool("warnStat", true);
    brightness = prefs.getUChar("bright", 255);
    nightModeBrighness = prefs.getUChar("nBright", 16);
    ledsColor = CRGB(prefs.getUInt("color", 0x00FF00));
    gradientColor = CRGB(prefs.getUInt("grad", 0xFF0000));
    pirEnabled = prefs.getBool("pirEn", true);
    pirDelay = prefs.getUInt("pirDel", 5);
    prefs.end();
  }
};

extern DeviceConfig cfg;

#endif