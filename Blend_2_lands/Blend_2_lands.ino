/*
   Demonstration on how to blend between two
   animations running at the same time
*/

#include "FastLED.h"

#define LED_DT 10
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define NUM_LEDS 7

uint8_t max_bright = 128;

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

void setup() {
  delay(1000);

  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);

  FastLED.setBrightness(max_bright);
  set_max_power_in_volts_and_milliamps(5, 500);
}

void loop() {

  animation_red();
  animation_green();

  // Alternate between 0 and 255 every minute
  uint8_t ratio = beatsin8(2);

  for (int i = 0; i < NUM_LEDS; i++) {
    // mix the 2 arrays together
    leds[i] = blend( leds2[i], leds3[i], ratio );
  }

  FastLED.show();

}

void animation_red() {
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t red = (millis() / 10) + (i * 12);
    if (red > 128) red = 0;
    leds2[i] = CRGB(red, 0, 0);
  }
}

void animation_green() {
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t green = (millis() / 5) - (i * 12);
    if (green > 128) green = 0;
    leds3[i] = CRGB(0, green, 0);
  }
}
