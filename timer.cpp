#include <Arduino.h>

static unsigned long previousMillis = 0;
static bool isRunning = false;

void startTimer() {
  previousMillis = millis();
  isRunning = true;
}

void stopTimer() {
  isRunning = false;
}

bool intervalHasPassed(unsigned long interval) {
  return millis() - previousMillis >= interval;
}

bool timerIsRunning() {
  return isRunning;
}