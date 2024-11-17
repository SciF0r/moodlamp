#include "led_helpers.h"
#include "timer.h"

static int currentLed = 0;

void runningLightsLoop() {
  currentLed = (currentLed + 1) % (NUM_LEDS * 2);
}

void runningLights(byte red, byte green, byte blue, int speedDelay) {
  if (timerIsRunning() && !intervalHasPassed(speedDelay)) {
    return;
  }
  startTimer();
  
  static int position = 0;
  position++;
  for(int i = 0; i < NUM_LEDS; i++) {
    setPixel(
      i,
      ((sin(i + position) * 127 + 128) / 255) * red,
      ((sin(i + position) * 127 + 128) / 255) * green,
      ((sin(i + position) * 127 + 128) / 255) * blue
    );
  }

  runningLightsLoop();
}