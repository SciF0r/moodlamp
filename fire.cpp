#include <Arduino.h>
#include "const.h"
#include "led_helpers.h"
#include "timer.h"

byte heat[NUM_LEDS];

void setPixelHeatColor(int pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
  // 0..63
  byte heatramp = t192 & 0x3F;
  // scale up to 0..252
  heatramp <<= 2;
 
  // figure out which third of the spectrum we're in:
  // hottest
  if (t192 > 0x80) {                     
    setPixel(pixel, 255, 255, heatramp);
  }
  // middle
  else if (t192 > 0x40 ) {             
    setPixel(pixel, 255, heatramp, 0);
  }
  // coolest
  else {                               
    setPixel(pixel, heatramp, 0, 0);
  }
}

// Cool down every cell a little
void cool_down(int cooling) {
  int cooldown;
  for (int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((cooling * 10) / NUM_LEDS) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    }
    else {
      heat[i] = heat[i] - cooldown;
    }
  }
}

// Heat from each cell drifts up and diffuses a little
void heat_up() {
  for (int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
}

// Randomly ignite new sparks near the bottom
void ignite(int sparking) {
  if (random(255) < sparking) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
  }
}

void fire(int cooling, int sparking, int speedDelay) {
  if (!timerIsRunning()) {
    startTimer();
  }
  else if (!intervalHasPassed(speedDelay)) {
    return;
  }

  cool_down(cooling);
  heat_up();
  ignite(sparking);

  for (int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j]);
  }
}