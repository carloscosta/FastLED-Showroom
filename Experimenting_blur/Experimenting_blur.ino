/* blur
 *
 * Experiment the blur function. If you look carefully at the animation, 
 * sometimes there's a smooth gradient between each LED. Other times, 
 * the difference between them is quite significant
 *
 */

#include "FastLED.h"

#define LED_DT 10
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define NUM_LEDS 7

uint8_t max_bright = 128;
struct CRGB leds[NUM_LEDS];

void setup() {
  delay(1000);

  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);

  FastLED.setBrightness(max_bright);
  set_max_power_in_volts_and_milliamps(5, 500); 
}

void loop() {
  // A sinewave at 3 Hz with values ranging from 64 to 192
  uint8_t blurAmount = dim8_raw(beatsin8(3,64, 192));

  // Apply some blurring to whatever's already on the strip, which will eventually go black
  blur1d(leds, NUM_LEDS, blurAmount);
  
  uint8_t  i = beatsin8(  9, 0, NUM_LEDS);
  uint8_t  j = beatsin8( 7, 0, NUM_LEDS);
  uint8_t  k = beatsin8(  5, 0, NUM_LEDS);
  
  // The color of each point shifts over time, each at a different speed
  uint16_t ms = millis();  
  
  leds[(i+j)/2] = CHSV( ms / 29, 200, 255);
  leds[(j+k)/2] = CHSV( ms / 41, 200, 255);
  leds[(k+i)/2] = CHSV( ms / 73, 200, 255);
  leds[(k+i+j)/3] = CHSV( ms / 53, 200, 255);
  
  FastLED.show(); 
}
 
