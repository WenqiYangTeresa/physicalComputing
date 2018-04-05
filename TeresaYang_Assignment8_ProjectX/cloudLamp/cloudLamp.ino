// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN_A            7 //9
#define PIN_B            8 //5
#define PIN_C            6 //5
#define PIN_D            9 //9
#define PIN_E            3 //5

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS_A      9
#define NUMPIXELS_B      5


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels_A = Adafruit_NeoPixel(NUMPIXELS_A, PIN_A, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_B = Adafruit_NeoPixel(NUMPIXELS_B, PIN_B, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_C = Adafruit_NeoPixel(NUMPIXELS_B, PIN_C, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_D = Adafruit_NeoPixel(NUMPIXELS_A, PIN_D, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_E = Adafruit_NeoPixel(NUMPIXELS_B, PIN_E, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels_A.begin(); // This initializes the NeoPixel library.
  pixels_B.begin();
  pixels_C.begin();
  pixels_D.begin();
  pixels_E.begin();
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
//blue
  for (int i = 0; i < NUMPIXELS_A; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_A.setPixelColor(i, pixels_A.Color(10, 0, 255)); // Moderately bright green color.

    pixels_A.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels_A.setBrightness(100);
  }
//pink
  for (int i = 0; i < NUMPIXELS_B; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_B.setPixelColor(i, pixels_B.Color(255, 170, 59)); // Moderately bright green color.

    pixels_B.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels_B.setBrightness(100);
  }
//cyan
  for (int i = 0; i < NUMPIXELS_B; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_C.setPixelColor(i, pixels_C.Color(255, 105, 59)); // Moderately bright green color.

    pixels_C.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels_C.setBrightness(100);
  }
  //purple
  for (int i = 0; i < NUMPIXELS_A; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_D.setPixelColor(i, pixels_D.Color(155, 25, 255)); // Moderately bright green color.

    pixels_D.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels_D.setBrightness(100);
  }
  //white
  for (int i = 0; i < NUMPIXELS_B; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_E.setPixelColor(i, pixels_E.Color(200, 125, 160)); // Moderately bright green color.

    pixels_E.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels_E.setBrightness(100);
  }
}
