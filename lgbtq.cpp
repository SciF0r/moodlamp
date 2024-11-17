#include "led_helpers.h"

enum Color {
  FIRST_COLOR,
  HOT_PINK,
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  TURQUOISE,
  INDIGO,
  VIOLET,
  LAST_COLOR
};

enum Direction {
  FADE_IN,
  FADE_OUT
};

static byte currentDirection = FADE_IN;
static byte currentColor = FIRST_COLOR + 1;
const int minSteps = 0;
const int maxSteps = 256;
static int currentStep = minSteps;

void lgbtqLoop() {
  if (currentDirection == FADE_IN) {
    currentStep++;
    if (currentStep >= maxSteps) {
      currentStep = maxSteps;
      currentDirection = FADE_OUT;
    }
  }
  else {
    currentStep -= 2;
    if (currentStep <= minSteps) {
      currentStep = minSteps;
      currentDirection = FADE_IN;
      currentColor++;
      if (currentColor == LAST_COLOR) {
        currentColor = FIRST_COLOR + 1;
      }
    }
  }
}

void setColor(byte red, byte green, byte blue) {
  float r = (currentStep / 256.0) * red;
  float g = (currentStep / 256.0) * green;
  float b = (currentStep / 256.0) * blue;
  setAllPixels(r, g, b);
}

void lgbtq() {
  switch (currentColor) {
    case HOT_PINK:
      setColor(0xe3, 0x1c, 0x79);
      break;
    case RED:
      setColor(0xff, 0x00, 0x00);
      break;
    case ORANGE:
      setColor(0xff, 0x50, 0x00);
      break;
    case YELLOW:
      setColor(0xff, 0x88, 0x00);
      break;
    case GREEN:
      setColor(0x00, 0xaa, 0x00);
      break;
    case TURQUOISE:
      setColor(0x00, 0x6e, 0x33);
      break;
    case INDIGO:
      setColor(0x15, 0x00, 0x80);
      break;
    case VIOLET:
      setColor(0x20, 0x00, 0x40);
      break;
  }

  lgbtqLoop();
}
