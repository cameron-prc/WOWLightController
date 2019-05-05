#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 1

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CHSV leds[NUM_LEDS];
int BRIGHTNESS_SHIFT_DELAY = 50;

CHSV blue;
CHSV orange;

int brighness = 0;

void setup() {
  blue = CHSV(160, 128, 255);
  orange = CHSV(160, 128, 255); 
  
  FastLED.addLeds<WS2812B, DATA_PIN, HSV>(leds, NUM_LEDS);
}

void loop() {
  pulse_colour(blue);
  pulse_colour(orange);
}

void pulse_colour(CHSV colour) {
  set_colour(colour);
  set_brightness(0);
  FastLED.show();

  while (brightness < 255) {
    increase_brightness(1);
    FastLED.show();

    delay(BRIGHTNESS_SHIFT_DELAY);
  }

  while (brightness > 0) {
    decrease_brightness(1);

    FastLED.show();

    delay(BRIGHTNESS_SHIFT_DELAY);
  }
}

void set_colour(CHSV colour) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = colour;
  }
}

void increase_brightness(int step) {

  int new_brightness = brightness + step;

  if (new_brightness >= 255) {
    new_brightness = 255;
  }

  set_brightness(new_brightness);
}

void decrease_brightness(int step) {
  
  int new_brightness = brightness - step;

  if (new_brightness < 0) {
    new_brightness = 0;
  }

  set_brightness(new_brightness);
}

void set_brightness(int new_brightness) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].maximizeBrightness(new_brightness);
  }
}
