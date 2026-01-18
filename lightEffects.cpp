#include "esp32-hal.h"
#include "lightEffects.h"

void rainbowARGB(CRGB *leds, int NUM_LEDS, int delay) {
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

void rainbowRGB(CRGB *leds, int NUM_LEDS, int delay) {
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

void setColor(CRGB *leds, int NUM_LEDS, CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
}

void thunder(CRGB *leds, int NUM_LEDS, CRGB color, int delay) {
  static int lastChange;
  if (lastChange + delay < millis()) {
    int startPoint = random(NUM_LEDS);
    if (startPoint > NUM_LEDS / 2) {
      for (int i = startPoint; i >= 0; i--) {
        leds[i] = color;
      }
    } else {
      for (int i = startPoint; i < NUM_LEDS; i++) {
        leds[i] = color;
      }
    }
    FastLED.clear();
    lastChange = millis();
  }
}

void gradient(CRGB *leds, int NUM_LEDS, CRGB startColor, CRGB endColor, int delay) {
  static int lastChange;
  static int offset;
  CRGB gradientColors[NUM_LEDS];
  fill_gradient_RGB(gradientColors, NUM_LEDS, startColor, endColor, startColor);
  if (lastChange + delay < millis()) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = gradientColors[(i + offset) % NUM_LEDS];
    }
    offset++;
    offset %= NUM_LEDS;
    lastChange = millis();
  }
}

bool catchWarning(CRGB *leds, int NUM_LEDS, int blinks, int delay) {
  static int currentIteration;
  static int lastChange;
  static bool status;
  if (currentIteration == blinks) {
    currentIteration = 0;
    return false;
  }
  if (lastChange + delay < millis()) {
    if (!status) {
      setColor(leds, NUM_LEDS, CRGB(255, 255, 0));
    } else {
      setColor(leds, NUM_LEDS, CRGB(0, 0, 0));
      currentIteration++;
    }
    status = !status;
    lastChange = millis();
  }
  return true;
}

bool startNightmodeState, hasTimerStarted;
int delaySec;
long lastChange;

void startPIR(int delaySeconds, bool &nightMode, bool &ledStatus) {
  startNightmodeState = nightMode;
  nightMode = true;
  ledStatus = true;
  delaySec = delaySeconds;
  hasTimerStarted = true;
  lastChange = millis();
}

void catchPIR(bool &nightMode, bool &ledStatus) {
  if (hasTimerStarted) {
    if (lastChange + delaySec * 1000 < millis()) {
      nightMode = startNightmodeState;
      ledStatus = false;
      hasTimerStarted = false;
    }
  }
}