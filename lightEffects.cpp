#include "esp32-hal.h"
#include "lightEffects.h"

int offset = 0;
long lastChange = 0;



void rainbowARGB(CRGB *leds, int NUM_LEDS, int delay) {
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
  if (lastChange + delay < millis()) {
    int startPoint = random(NUM_LEDS);
    if (startPoint > NUM_LEDS / 2) {
      for (int i = startPoint; i >= 0; i--) {
        leds[i] = color;
        FastLED.show();
      }
    } else {
      for (int i = startPoint; i < NUM_LEDS; i++) {
        leds[i] = color;
        FastLED.show();
      }
    }
    FastLED.clear();
    lastChange = millis();
  }
}

void gradient(CRGB *leds, int NUM_LEDS, CRGB startColor, CRGB endColor, int delay) {
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
