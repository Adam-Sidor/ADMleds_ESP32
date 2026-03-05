#include "esp32-hal.h"
#include "lightEffects.h"
#include "GlobalConfig.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;
extern DeviceConfig cfg;

void rainbowARGB(int delay) {
  static int lastChange;
  static int offset;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setHue(map(i, 0, NUM_LEDS - 1, 0, 255) + offset);
  }
  if (lastChange + delay < millis()) {
    offset++;
    offset %= 256;
    lastChange = millis();
  }
}

void rainbowRGB(int delay) {
  static int lastChange;
  static int offset;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setHue(offset);
  }
  if (lastChange + delay < millis()) {
    offset++;
    offset %= 256;
    lastChange = millis();
  }
}

void setColor() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = cfg.ledsColor;
  }
}

void thunder(int delay) {
  static int lastChange;
  if (lastChange + delay < millis()) {
    int startPoint = random(NUM_LEDS);
    if (startPoint > NUM_LEDS / 2) {
      for (int i = startPoint; i >= 0; i--) {
        leds[i] = cfg.ledsColor;
      }
      FastLED.show();
    } else {
      for (int i = startPoint; i < NUM_LEDS; i++) {
        leds[i] = cfg.ledsColor;
      }
      FastLED.show();
    }
    FastLED.clear();
    lastChange = millis();
  }
}

void gradient(int delay) {
  static int lastChange;
  static int offset;
  CRGB gradientColors[NUM_LEDS];
  fill_gradient_RGB(gradientColors, NUM_LEDS, cfg.ledsColor, cfg.gradientColor, cfg.ledsColor);
  if (lastChange + delay < millis()) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = gradientColors[(i + offset) % NUM_LEDS];
    }
    offset++;
    offset %= NUM_LEDS;
    lastChange = millis();
  }
}

bool catchWarning(int blinks, int delay) {
  static int currentIteration;
  static int lastChange;
  static bool status;
  if (currentIteration == blinks) {
    currentIteration = 0;
    return false;
  }
  if (lastChange + delay < millis()) {
    if (!status) {
      for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB(255, 255, 0);
    } else {
      for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB(0, 0, 0);
      currentIteration++;
    }
    status = !status;
    lastChange = millis();
  }
  return true;
}