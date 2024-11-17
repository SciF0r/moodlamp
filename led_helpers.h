#ifndef LED_HELPERS_H
#define LED_HELPERS_H

#include "FastLED.h"

extern CRGB leds[];

void showStrip();
void setPixel(int Pixel, byte red, byte green, byte blue);
void setAllPixels(byte red, byte green, byte blue);

#endif