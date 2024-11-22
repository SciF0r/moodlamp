#include "const.h"
#include "led_helpers.h"
#include "timer.h"

const byte red = 0;
const byte green = 1;
const byte blue = 2;

static byte currentOffset = 0;
static byte chaseOffset = 0;

byte* wheelColor(int ledPosition) {
  byte wheelPosition = (ledPosition + currentOffset) % 256;
  static byte c[3];
  if (wheelPosition < 85) {
    c[red] = wheelPosition * 3;
    c[green] = 255 - wheelPosition * 3;
    c[blue] = 0;
  }
  else if (wheelPosition < 170) {
    wheelPosition -= 85;
    c[red] = 255 - wheelPosition * 3;
    c[green] = 0;
    c[blue] = wheelPosition * 3;
  }
  else {
    wheelPosition -= 170;
    c[red] = 0;
    c[green] = wheelPosition * 3;
    c[blue] = 255 - wheelPosition * 3;
  }
  return c;
}

void rainbowLoop() {
  currentOffset = (currentOffset + 1) % 256;
}

void rainbowCycle(int speedDelay) {
  if (timerIsRunning() && !intervalHasPassed(speedDelay)) {
    return;
  }
  startTimer();

  byte *color;
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    int normalizedPosition = ledIndex * 256 / NUM_LEDS;
    color = wheelColor(normalizedPosition);
    setPixel(ledIndex, color[red], color[green], color[blue]);
  }

  rainbowLoop();
}

void rainbowTheaterChaseLoop() {
  chaseOffset = (chaseOffset + 1) % 3;
  if (chaseOffset == 0) {
    currentOffset = (currentOffset + 1) % 256;
  }
}

void rainbowTheaterChase(int speedDelay) {
  if (!timerIsRunning()) {
    currentOffset = 0;
  }
  if (timerIsRunning() && !intervalHasPassed(speedDelay)) {
    return;
  }
  startTimer();

  byte* color;
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex += 3) {
    color = wheelColor(ledIndex);
    byte ledWithStep = (ledIndex + chaseOffset) % NUM_LEDS;
    setPixel(ledWithStep, color[red], color[green], color[blue]);
    setPixel((ledWithStep - 1) % NUM_LEDS, 0, 0, 0);
  }

  rainbowTheaterChaseLoop();
}