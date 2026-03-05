#ifndef LIGHT_EFFECTS_H
#define LIGHT_EFFECTS_H

#include <FastLED.h>

void rainbowARGB(int delay);
void rainbowRGB(int delay);
void setColor();
void thunder(int delay);
void gradient(int delay);
bool catchWarning(int blinks, int delay);

#endif