#include "const.h"
#include "led_helpers.h"
#include "timer.h"

static int currentLed = 0;
const int distanceBetweenMeteors = NUM_LEDS/2;

void meteorRainLoop() {
  currentLed++;
  if (currentLed == NUM_LEDS + distanceBetweenMeteors) {
    currentLed = 0;
  }
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, bool meteorRandomDecay, int speedDelay) {
  if (timerIsRunning() && !intervalHasPassed(speedDelay)) {
    return;
  }
  else if (!timerIsRunning()) {
    setAllPixels(0, 0, 0);
  }
  startTimer();

  for (int i = 0; i < NUM_LEDS; i++) {
    if (!meteorRandomDecay || random(10) > 5) {
      leds[i].fadeToBlackBy(meteorTrailDecay);
    }
  }

  for (int i = 0; i < meteorSize; i++) {
    int led = currentLed - i;
    if (led < NUM_LEDS && led >= 0) {
      setPixel(led, red, green, blue);
    }
  }

  meteorRainLoop();
}