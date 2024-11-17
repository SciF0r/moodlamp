#include "led_helpers.h"

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, bool meteorRandomDecay, int speedDelay) {
  if (timerIsRunning() && !intervalHasPassed(speedDelay)) {
    return;
  }
  startTimer();

  setAllPixels(0, 0, 0);

  for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      if (!meteorRandomDecay || random(10) > 5) {
        leds[j].fadeToBlackBy(meteorTrailDecay);
      }
    }
  
    for (int j = 0; j < meteorSize; j++) {
      int currentLed = i - j;
      if (currentLed < NUM_LEDS && currentLed >= 0) {
        setPixel(currentLed, red, green, blue);
      } 
    }
  }
}