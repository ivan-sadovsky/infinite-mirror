#define NUM_LEDS 100
#define LED_PIN 6

#define CURRENT_LIMIT 2000    // current limit [mA]; 0 - no limit
#define BRIGHTNESS 250        // [0-255]

#define EFFECT_DELAY_TIME 100  // [msec]
#define FADE_STEP 5

#include <FastLED.h>
CRGB leds[NUM_LEDS];

unsigned long effectDelayStart = 0;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  if (CURRENT_LIMIT > 0)
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  randomSeed(analogRead(0));
  
  effectDelayStart = millis();
}

void loop() {
  if (millis() - effectDelayStart < EFFECT_DELAY_TIME)
    return;
  effectDelayStart = millis();
  
  byte thisNum = random(0, NUM_LEDS);
  //if (getPixelColor(thisNum) == 0)
    leds[thisNum] = CRGB(255, random(0, 127), random(0, 31));
  fade();
  FastLED.show();
}

uint32_t getPixelColor(int pixelIndex) {
  return (((uint32_t)leds[pixelIndex].r << 16) | ((long)leds[pixelIndex].g << 8 ) | (long)leds[pixelIndex].b);
}

void fade() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if ((uint32_t)getPixelColor(i) == 0) continue;
    leds[i].fadeToBlackBy(FADE_STEP);
  }
}
