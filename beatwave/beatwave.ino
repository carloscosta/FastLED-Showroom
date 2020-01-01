/* beatwave

   Animation combining coloured wave values from
   several beatsin8() functions
*/

#include "FastLED.h"

#define LED_DT 10
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define NUM_LEDS 7

uint8_t max_bright = 128;
struct CRGB leds[NUM_LEDS];

// Palette definitions
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;
TBlendType    currentBlending = LINEARBLEND;

void setup() {
  delay(1000);

  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);

  currentPalette = RainbowColors_p;

  FastLED.setBrightness(max_bright);

  // FastLED Power management set at 5V, 500mA
  set_max_power_in_volts_and_milliamps(5, 500);
}

void loop() {
  beatwave();

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
  }

  EVERY_N_SECONDS(5) {
    // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 192, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)));
  }

  FastLED.show();

}

void beatwave() {
  uint8_t wave1 = beatsin8(9, 0, 255);
  uint8_t wave2 = beatsin8(8, 0, 255);
  uint8_t wave3 = beatsin8(7, 0, 255);
  uint8_t wave4 = beatsin8(6, 0, 255);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, i + wave1 + wave2 + wave3 + wave4, 255, currentBlending);
  }
}
