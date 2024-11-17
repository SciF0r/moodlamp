#include "FastLED.h"
#include "const.h"
#include "fire.h"
#include "led_helpers.h"
#include "lgbtq.h"
#include "meteor_rain.h"
#include "rainbow.h"
#include "running_lights.h"
#include "timer.h"
#include "twinkle.h"

#define BUTTON 2
#define BRIGHTNESS 100
#define LED_PIN 5
#define LED_TYPE WS2812

enum Effect {
  START_OF_EFFECTS,
  FIRE,
  LGBTQ,
  RAINBOW_CYCLE,
  //RAINBOW_THEATER_CHASE,
  METEOR_RAIN,
  TWINKLE,
  TWINKLE_RANDOM,
  TWINKLE_RANDOM_SINGLE,
  RUNNING_LIGHTS,
  TEST,
  END_OF_EFFECTS
};
static byte defaultEffect = TEST;
static byte selectedEffect = defaultEffect;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), changeEffect, CHANGE);
  FastLED.clear();
  Serial.begin(9600);
}

void loop() {
  FastLED.setBrightness(BRIGHTNESS);

  if (selectedEffect >= END_OF_EFFECTS) {
    selectedEffect = START_OF_EFFECTS + 1;
  }

  switch (selectedEffect) {

    case FIRE:
      {
        int coolingRate = 55;
        int sparkingRate = 90;
        int speedDelay = 60;
        fire(coolingRate, sparkingRate, speedDelay);
        break;
      }

    case LGBTQ:
      {
        lgbtq();
        break;
      }

    case RAINBOW_CYCLE:
      {
        int speedDelay = 20;
        rainbowCycle(speedDelay);
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

    case TWINKLE:
      {
        twinkle(0x25, 0x00, 0x05, 20, 400, false);
        break;
      }

    case TWINKLE_RANDOM:
      {
        twinkleRandom(20, 400, false);
        break;
      }

    case TWINKLE_RANDOM_SINGLE:
      {
        twinkleRandom(20, 200, true);
        break;
      }

      // case TEST: {
      //             // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay
      //             SnowSparkle(0x10, 0x10, 0x10, 20, random(100,1000));
      //             break;
      //           }

    case RUNNING_LIGHTS:
      {
        runningLights(0x25, 0x00, 0x05, 50);
        break;
      }

      // case 11 : {
      //             // colorWipe - Color (red, green, blue), speed delay
      //             colorWipe(0x00,0xff,0x00, 50);
      //             colorWipe(0x00,0x00,0x00, 50);
      //             break;
      //           }

      // case 13 : {
      //             // theatherChase - Color (red, green, blue), speed delay
      //             theaterChase(0xff,0,0,50);
      //             break;
      //           }

      // case 14 : {
      //             // theaterChaseRainbow - Speed delay
      //             theaterChaseRainbow(50);
      //             break;
      //           }


      // case 16 : {
      //             // mimic BouncingBalls
      //             byte onecolor[1][3] = { {0xff, 0x00, 0x00} };
      //             BouncingColoredBalls(1, onecolor, false);
      //             break;
      //           }

      // case 17 : {
      //             // multiple colored balls
      //             byte colors[3][3] = { {0xff, 0x00, 0x00},
      //                                   {0xff, 0xff, 0xff},
      //                                   {0x00, 0x00, 0xff} };
      //             BouncingColoredBalls(3, colors, false);
      //             break;
      //           }
  }

  FastLED.show();
}

void changeEffect() {
  if (digitalRead(BUTTON) == HIGH) {
    selectedEffect++;
    stopTimer();
  }
}

// *************************
// ** LEDEffect Functions **
// *************************

void RGBLoop() {
  for (int j = 0; j < 3; j++) {
    // Fade IN
    for (int k = 0; k < 256; k++) {
      switch (j) {
        case 0: setAllPixels(k, 0, 0); break;
        case 1: setAllPixels(0, k, 0); break;
        case 2: setAllPixels(0, 0, k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for (int k = 255; k >= 0; k--) {
      switch (j) {
        case 0: setAllPixels(k, 0, 0); break;
        case 1: setAllPixels(0, k, 0); break;
        case 2: setAllPixels(0, 0, k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause) {
  for (int j = 0; j < StrobeCount; j++) {
    setAllPixels(red, green, blue);
    showStrip();
    delay(FlashDelay);
    setAllPixels(0, 0, 0);
    showStrip();
    delay(FlashDelay);
  }

  delay(EndPause);
}

void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAllPixels(red, green, blue);

  int Pixel = random(NUM_LEDS);
  setPixel(Pixel, 0xff, 0xff, 0xff);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel, red, green, blue);
  showStrip();
  delay(SpeedDelay);
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position = 0;

  for (int i = 0; i < NUM_LEDS * 2; i++) {
    Position++;  // = 0; //Position + Rate;
    for (int i = 0; i < NUM_LEDS; i++) {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * 127 + 128;
      //setPixel(i,level,0,0);
      //float level = sin(i+Position) * 127 + 128;
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red,
               ((sin(i + Position) * 127 + 128) / 255) * green,
               ((sin(i + Position) * 127 + 128) / 255) * blue);
    }

    showStrip();
    delay(WaveDelay);
  }
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    setPixel(i, red, green, blue);
    showStrip();
    delay(SpeedDelay);
  }
}

// used by rainbowCycle and theaterChaseRainbow


void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j = 0; j < 10; j++) {  //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        setPixel(i + q, red, green, blue);  //turn every third pixel on
      }
      showStrip();

      delay(SpeedDelay);

      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        setPixel(i + q, 0, 0, 0);  //turn every third pixel off
      }
    }
  }
}



void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous) {
  float Gravity = -9.81;
  int StartHeight = 1;

  float Height[BallCount];
  float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int Position[BallCount];
  long ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  boolean ballBouncing[BallCount];
  boolean ballsStillBouncing = true;

  for (int i = 0; i < BallCount; i++) {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
    ballBouncing[i] = true;
  }

  while (ballsStillBouncing) {
    for (int i = 0; i < BallCount; i++) {
      TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow(TimeSinceLastBounce[i] / 1000, 2.0) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

      if (Height[i] < 0) {
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();

        if (ImpactVelocity[i] < 0.01) {
          if (continuous) {
            ImpactVelocity[i] = ImpactVelocityStart;
          } else {
            ballBouncing[i] = false;
          }
        }
      }
      Position[i] = round(Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    ballsStillBouncing = false;  // assume no balls bouncing
    for (int i = 0; i < BallCount; i++) {
      setPixel(Position[i], colors[i][0], colors[i][1], colors[i][2]);
      if (ballBouncing[i]) {
        ballsStillBouncing = true;
      }
    }

    showStrip();
    setAllPixels(0, 0, 0);
  }
}