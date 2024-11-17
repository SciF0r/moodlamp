#include "FastLED.h"
#include "const.h"
#include "fire.h"
#include "led_helpers.h"
#include "lgbtq.h"
#include "timer.h"

#define BUTTON 2
#define BRIGHTNESS 100
#define LED_PIN 5
#define LED_TYPE WS2812

enum Effect {
  START_OF_EFFECTS,
  FIRE,
  LGBTQ,
  // RAINBOW,
  // METEOR_RAIN,
  // TEST,
  END_OF_EFFECTS
};
static byte defaultEffect = FIRE;
static byte selectedEffect = defaultEffect;

void setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), changeEffect, CHANGE);
  FastLED.clear();
}

void loop() { 
  FastLED.setBrightness(BRIGHTNESS);

  if (selectedEffect >= END_OF_EFFECTS) {
    selectedEffect = START_OF_EFFECTS+1;
  }

  switch(selectedEffect) {
  
    case FIRE:
    {
      int coolingRate = 55;
      int sparkingRate = 90;
      int speedDelay = 60;
      Serial.println(speedDelay);
      fire(coolingRate, sparkingRate, speedDelay);
      break;
    }

    case LGBTQ:
    {
      lgbtq();
      break;
    }

    // case RAINBOW:
    // {
    //   int speedDelay = 20;
    //   rainbowCycle(speedDelay);
    //   break;
    // }

    // case METEOR_RAIN:
    // {
    //   int meteorSize = 10;
    //   int trailDecay = 64;
    //   bool randomTrailDecay = true;
    //   int speedDelay = 30;
    //   meteorRain(0x25, 0x00, 0x05, meteorSize, trailDecay, randomTrailDecay, speedDelay);
    //   break;
    // }

    // case TEST: {
    //             // HalloweenEyes - Color (red, green, blue), Size of eye, space between eyes, fade (true/false), steps, fade delay, end pause
    //             HalloweenEyes(0xff, 0x00, 0x00, 
    //                           1, 4, 
    //                           true, random(5,50), random(50,150), 
    //                           random(1000, 10000));
    //             HalloweenEyes(0xff, 0x00, 0x00, 
    //                           1, 4, 
    //                           true, random(5,50), random(50,150), 
    //                           random(1000, 10000));
    //             break;
    //           }
              
    // case 4  : {
    //             // CylonBounce - Color (red, green, blue), eye size, speed delay, end pause
    //             CylonBounce(0xff, 0x00, 0x00, 4, 10, 50);
    //             break;
    //           }
              
    // case 5  : {
    //             // NewKITT - Color (red, green, blue), eye size, speed delay, end pause
    //             NewKITT(0xff, 0x00, 0x00, 8, 10, 50);
    //             break;
    //           }
              
    // case 6  : {
    //             // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false) 
    //             Twinkle(0xff, 0x00, 0x00, 10, 100, false);
    //             break;
    //           }
              
    // case 7  : { 
    //             // TwinkleRandom - twinkle count, speed delay, only one (true/false)
    //             TwinkleRandom(20, 100, false);
    //             break;
    //           }
              
    // case 8  : {
    //             // Sparkle - Color (red, green, blue), speed delay
    //             Sparkle(0xff, 0xff, 0xff, 0);
    //             break;
    //           }
               
    // case 9  : {
    //             // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay
    //             SnowSparkle(0x10, 0x10, 0x10, 20, random(100,1000));
    //             break;
    //           }
              
    // case 10 : {
    //             // Running Lights - Color (red, green, blue), wave dealy
    //             RunningLights(0xff,0x00,0x00, 50);  // red
    //             RunningLights(0xff,0xff,0xff, 50);  // white
    //             RunningLights(0x00,0x00,0xff, 50);  // blue
    //             break;
    //           }
              
    // case 11 : {
    //             // colorWipe - Color (red, green, blue), speed delay
    //             colorWipe(0x00,0xff,0x00, 50);
    //             colorWipe(0x00,0x00,0x00, 50);
    //             break;
    //           }

    // case 12 : {
    //             // rainbowCycle - speed delay
    //             rainbowCycle(20);
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

    // case 15 : {
    //             // Fire - Cooling rate, Sparking rate, speed delay
    //             Fire(55,90,60);
    //             break;
    //           }


    //           // simple bouncingBalls not included, since BouncingColoredBalls can perform this as well as shown below
    //           // BouncingColoredBalls - Number of balls, color (red, green, blue) array, continuous
    //           // CAUTION: If set to continuous then this effect will never stop!!! 
              
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

    // case 18 : {
    //             // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay 
    //             meteorRain(0x25, 0x00, 0x05, 10, 64, true, 30);
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

void RGBLoop(){
  for(int j = 0; j < 3; j++ ) { 
    // Fade IN
    for(int k = 0; k < 256; k++) { 
      switch(j) { 
        case 0: setAllPixels(k,0,0); break;
        case 1: setAllPixels(0,k,0); break;
        case 2: setAllPixels(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAllPixels(k,0,0); break;
        case 1: setAllPixels(0,k,0); break;
        case 2: setAllPixels(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}



void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAllPixels(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAllPixels(0,0,0);
    showStrip();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}

void HalloweenEyes(byte red, byte green, byte blue, 
                   int EyeWidth, int EyeSpace, 
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause){
  randomSeed(analogRead(0));
  
  int i;
  int StartPoint  = random( 0, NUM_LEDS - (2*EyeWidth) - EyeSpace );
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;
  
  for(i = 0; i < EyeWidth; i++) {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
  }
  
  showStrip();
  
  if(Fade==true) {
    float r, g, b;
  
    for(int j = Steps; j >= 0; j--) {
      r = j*(red/Steps);
      g = j*(green/Steps);
      b = j*(blue/Steps);
      
      for(i = 0; i < EyeWidth; i++) {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
      }
      
      showStrip();
      delay(FadeDelay);
    }
  }
  
  setAllPixels(0,0,0); // Set all black
  
  delay(EndPause);
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAllPixels(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAllPixels(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}

void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

// used by NewKITT
void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i =((NUM_LEDS-EyeSize)/2); i>=0; i--) {
    setAllPixels(0,0,0);
    
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
    
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i<=((NUM_LEDS-EyeSize)/2); i++) {
    setAllPixels(0,0,0);
    
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
    
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAllPixels(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAllPixels(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAllPixels(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),red,green,blue);
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAllPixels(0,0,0);
     }
   }
  
  delay(SpeedDelay);
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAllPixels(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAllPixels(0,0,0);
     }
   }
  
  delay(SpeedDelay);
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}

void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAllPixels(red,green,blue);
  
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,0xff,0xff,0xff);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      showStrip();
      delay(WaveDelay);
  }
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      setPixel(i, red, green, blue);
      showStrip();
      delay(SpeedDelay);
  }
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

// used by rainbowCycle and theaterChaseRainbow
byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, red, green, blue);    //turn every third pixel on
      }
      showStrip();
     
      delay(SpeedDelay);
     
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, 0,0,0);        //turn every third pixel off
      }
    }
  }
}

void theaterChaseRainbow(int SpeedDelay) {
  byte *c;
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < NUM_LEDS; i=i+3) {
          c = Wheel( (i+j) % 255);
          setPixel(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        showStrip();
       
        delay(SpeedDelay);
       
        for (int i=0; i < NUM_LEDS; i=i+3) {
          setPixel(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous) {
  float Gravity = -9.81;
  int StartHeight = 1;
  
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  boolean ballBouncing[BallCount];
  boolean ballsStillBouncing = true;
  
  for (int i = 0 ; i < BallCount ; i++) {   
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
    ballBouncing[i]=true;
  }

  while (ballsStillBouncing) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
  
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
  
        if ( ImpactVelocity[i] < 0.01 ) {
          if (continuous) {
            ImpactVelocity[i] = ImpactVelocityStart;
          } else {
            ballBouncing[i]=false;
          }
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    ballsStillBouncing = false; // assume no balls bouncing
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],colors[i][0],colors[i][1],colors[i][2]);
      if ( ballBouncing[i] ) {
        ballsStillBouncing = true;
      }
    }
    
    showStrip();
    setAllPixels(0,0,0);
  }
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAllPixels(0, 0, 0);

  for (int i=0; i < NUM_LEDS+NUM_LEDS; i++) {
    // fade brightness all LEDs one step
    for (int j=0; j<NUM_LEDS; j++) {
      if (!meteorRandomDecay || random(10) > 5) {
        fadeToBlack(j, meteorTrailDecay);
      }
    }

    // draw meteor
    for (int j=0; j<meteorSize; j++) {
      if(i-j < NUM_LEDS && i-j >= 0) {
        setPixel(i-j, red, green, blue);
      } 
    }

    showStrip();
    delay(SpeedDelay);
  }
}

// used by meteorrain
void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}