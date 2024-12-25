#include "lightEffects.h"

int offset=0;

void rainbowARGB(CRGB *leds,int NUM_LEDS){
    for(int i=0;i<NUM_LEDS;i++){
        leds[i].setHue(map(i,0,NUM_LEDS-1,0,255)+offset);
    }
    offset++;
    offset%=256;
}