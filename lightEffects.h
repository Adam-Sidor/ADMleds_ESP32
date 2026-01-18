#include <FastLED.h>

void rainbowARGB(CRGB *leds,int NUM_LEDS,int delay);
void rainbowRGB(CRGB *leds,int NUM_LEDS,int delay);
void setColor(CRGB *leds,int NUM_LEDS,CRGB color);
void thunder(CRGB *leds,int NUM_LEDS,CRGB color,int delay);
void gradient(CRGB *leds,int NUM_LEDS,CRGB startColor,CRGB endColor,int delay);
bool catchWarning(CRGB *leds, int NUM_LEDS, int blinks, int delay);