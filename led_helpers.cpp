#include <Arduino.h>
#include "FastLED.h"
#include "const.h"

CRGB leds[NUM_LEDS];

void showStrip() {
  FastLED.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void setAllPixels(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}