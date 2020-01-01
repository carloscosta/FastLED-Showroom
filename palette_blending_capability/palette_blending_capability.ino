/*
    Simple non-blocking FastLED display sequence template

*/

#include "FastLED.h"

// A digital unsigned subtraction macro. if result <0, then x=0. Otherwise, x=b
#define qsubd(x, b) ((x>b)?b:0)

// Unsigned subtraction macro. if result <0, then x=0. Otherwise x=x-b
#define qsuba(x, b) ((x>b)?x-b:0)

#define LED_DT 10
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define NUM_LEDS 7

uint8_t max_bright = 128;

struct CRGB leds[NUM_LEDS];

// Palette definitions
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;

// NOBLEND or LINEARBLEND
TBlendType currentBlending;

// Define variables used by the sequences
int twinkrate = 100; // The higher the value, the lower the number of twinkles
uint8_t thisdelay =  10; // A delay value for the sequence(s)
uint8_t thisfade =   8; // How quickly does it fade? Lower = slower fade rate
uint8_t thishue =  50; // The hue
uint8_t thissat = 255; // The saturation, where 255 = brilliant colours
uint8_t thisbri = 255; // Brightness of a sequence
bool randhue =   1; // Do we want random colours all the time? 1 = yes

void setup() {
  delay(1000);
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812

  currentBlending = LINEARBLEND;

  FastLED.setBrightness(max_bright);

  // FastLED Power management set at 5V, 500mA
  set_max_power_in_volts_and_milliamps(5, 500);
}


void loop () {
  // Check the demo loop for changes to the variables.
  ChangeMe();

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24;

    // AWESOME palette blending capability
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
  }

  // FastLED based non-blocking delay to update/display the sequence
  EVERY_N_MILLISECONDS(thisdelay) {
    twinkle();
  }

  // Change the target palette to a random one every 5 seconds
  EVERY_N_SECONDS(5) {
    static uint8_t baseC = random8();
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 192, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)));
  }

  FastLED.show();
}

void twinkle() {
  if (random8() < twinkrate)
    leds[random16(NUM_LEDS)] += ColorFromPalette(currentPalette, (randhue ? random8() : thishue), 255, currentBlending);

  fadeToBlackBy(leds, NUM_LEDS, thisfade);
}

// A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence
void ChangeMe() {
  uint8_t secondHand = (millis() / 1000) % 10;

  // Static variable, means it's only defined once. This is our 'debounce' variable
  static uint8_t lastSecond = 99;

  if (lastSecond != secondHand) {

    // Debounce to make sure we're not repeating an assignment
    lastSecond = secondHand;

    switch (secondHand) {
      case 0: thisdelay = 10; randhue = 1; thissat = 255; thisfade = 8; twinkrate = 150; break;
      case 5: thisdelay = 100; randhue = 0;  thishue = random8(); thisfade = 2; twinkrate = 20; break;
      case 10: break;
    }
  }
}
