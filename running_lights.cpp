#include "const.h"
#include "led_helpers.h"
#include "lgbtq_colors.h"
#include "timer.h"

static int currentLed = 0;
static int currentColor = HOT_PINK;

void runningLightsLoop() {
  currentLed = (currentLed + 1) % NUM_LEDS;
  if (currentLed == 0) {
    currentColor = (currentColor + 1) % LAST_COLOR;
  }
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

void runningLightsLgbtq(int speedDelay) {
  byte *color = lgbtqColors[currentColor];
  runningLights(color[0], color[1], color[2], speedDelay);
}