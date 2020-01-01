/*
   Uses beats, blend and the fill gradient functions to blend a
   couple of waves together
*/

#include "FastLED.h"

#define LED_DT 10
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define NUM_LEDS 7

uint8_t max_bright = 128;

struct CRGB leds[NUM_LEDS];

CRGB clr1;
CRGB clr2;
uint8_t speed;
uint8_t loc1;
uint8_t loc2;
uint8_t ran1;
uint8_t ran2;

void setup() {
  delay(1000);
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812

  FastLED.setBrightness(max_bright);
  set_max_power_in_volts_and_milliamps(5, 500);
}

void loop() {
  beats_blend();
  FastLED.show();
}

void beats_blend() {
  speed = beatsin8(6, 0, 255);

  clr1 = blend(CHSV(beatsin8(3, 0, 255), 255, 255), CHSV(beatsin8(4, 0, 255), 255, 255), speed);
  clr2 = blend(CHSV(beatsin8(4, 0, 255), 255, 255), CHSV(beatsin8(3, 0, 255), 255, 255), speed);

  loc1 = beatsin8(10, 0, NUM_LEDS - 1);

  fill_gradient_RGB(leds, 0, clr2, loc1, clr1);
  fill_gradient_RGB(leds, loc1, clr2, NUM_LEDS - 1, clr1);
}
