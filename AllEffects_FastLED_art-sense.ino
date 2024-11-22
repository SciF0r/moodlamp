#include "FastLED.h"
#include "const.h"
#include "fire.h"
#include "led_helpers.h"
#include "lgbtq.h"
#include "meteor_rain.h"
#include "rainbow.h"
#include "running_lights.h"
#include "timer.h"

#define BUTTON 2
#define BRIGHTNESS 100
#define LED_PIN 5
#define LED_TYPE WS2812

enum Effect {
  FIRE,
  LGBTQ,
  RAINBOW_CYCLE,
  RAINBOW_THEATER_CHASE,
  METEOR_RAIN,
  RUNNING_LIGHTS,
  END_OF_EFFECTS
};
static byte selectedEffect = FIRE;
static bool effectChanged = false;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), changeEffect, CHANGE);
  FastLED.clear();
  Serial.begin(9600);
}

void loop() {
  FastLED.setBrightness(BRIGHTNESS);

  if (effectChanged) {
    stopTimer();
    setAllPixels(0, 0, 0);
    effectChanged = false;
  }

  switch (selectedEffect) {

    case FIRE:
      {
        int coolingRate = 55;
        int sparkingRate = 90;
        int speedDelay = 120;
        fire(coolingRate, sparkingRate, speedDelay);
        break;
      }

    case LGBTQ:
      {
        int speedDelay = 50;
        lgbtq(speedDelay);
        break;
      }

    case RAINBOW_CYCLE:
      {
        int speedDelay = 20;
        rainbowCycle(speedDelay);
        break;
      }

    case RAINBOW_THEATER_CHASE:
      {
        int speedDelay = 200;
        rainbowTheaterChase(speedDelay);
        break;
      }

    case METEOR_RAIN:
      {
        int meteorSize = 10;
        int trailDecay = 64;
        bool randomTrailDecay = true;
        int speedDelay = 30;
        meteorRain(0x25, 0x00, 0x05, meteorSize, trailDecay, randomTrailDecay, speedDelay);
        break;
      }

    case RUNNING_LIGHTS:
      {
        int speedDelay = 100;
        runningLightsLgbtq(speedDelay);
        break;
      }
  }

  FastLED.show();
}

void changeEffect() {
  if (digitalRead(BUTTON) == HIGH) {
    selectedEffect = (selectedEffect + 1) % END_OF_EFFECTS;
    effectChanged = true;
  }
}