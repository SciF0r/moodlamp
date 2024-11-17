#include "const.h"
#include "led_helpers.h"
#include "timer.h"

static int currentTwinkle = 0;

void twinkleLoop() {
  currentTwinkle++;
}

void twinkle(byte red, byte green, byte blue, int count, int speedDelay, bool onlyOne) {
  if (timerIsRunning() && !intervalHasPassed(speedDelay)) {
    return;
  }
  startTimer();

  if (currentTwinkle > count) {
    currentTwinkle = 0;
  }

  if (onlyOne || currentTwinkle == 0) {
    setAllPixels(0,0,0);
  }

  setPixel(random(NUM_LEDS), red, green, blue);
  twinkleLoop();
}

void twinkleRandom(int count, int speedDelay, bool onlyOne) {
  twinkle(random(0, 255), random(0, 255), random(0, 255), count, speedDelay, onlyOne);
}