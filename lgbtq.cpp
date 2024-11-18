#include "const.h"
#include "led_helpers.h"
#include "lgbtq_colors.h"
#include "timer.h"

static int currentLed = 0;
static byte currentColor = HOT_PINK;

void lgbtqLoop() {
  currentLed = (currentLed + 1) % NUM_LEDS;

  if (currentLed == 0) {
    currentLed = 2 * NUM_LEDS / 3;
    currentColor = (currentColor + 1) % LAST_COLOR;
  }
}

void lgbtq(int speedDelay) {
  if (timerIsRunning() && !intervalHasPassed(speedDelay)) {
    return;
  }
  else if (!timerIsRunning()) {
    currentLed = 2 * NUM_LEDS / 3;
  }
  startTimer();

  int numLedsAll = NUM_LEDS;
  int numLedsThird = NUM_LEDS / 3;
  int numLedsTwoThirds = 2 * NUM_LEDS / 3;

  byte *color = lgbtqColors[currentColor];
  byte *colorPlus1 = lgbtqColors[(currentColor + 1) % LAST_COLOR];
  byte *colorPlus2 = lgbtqColors[(currentColor + 2) % LAST_COLOR];

  setPixel(currentLed, color[0], color[1], color[2]);
  if (currentLed >= numLedsThird) {
    byte *colorPlus1 = lgbtqColors[(currentColor + 1) % LAST_COLOR];
    setPixel(currentLed - numLedsThird, colorPlus1[0], colorPlus1[1], colorPlus1[2]);
  }
  if (currentLed >= numLedsTwoThirds) {
    byte *colorPlus2 = lgbtqColors[(currentColor + 2) % LAST_COLOR];
    setPixel(currentLed - numLedsTwoThirds, colorPlus2[0], colorPlus2[1], colorPlus2[2]);
  }

  lgbtqLoop();
}