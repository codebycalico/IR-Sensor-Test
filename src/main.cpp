#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 2
#define TOTAL_LEDS_OUTER_RING 12
#define TOTAL_LEDS_INNER_RING 19
#define TOTAL_LEDS (TOTAL_LEDS_INNER_RING + TOTAL_LEDS_OUTER_RING)

CRGBArray <TOTAL_LEDS_OUTER_RING + TOTAL_LEDS_INNER_RING> ledRing;
CRGB* ledInnerRing = &ledRing[TOTAL_LEDS_OUTER_RING];

uint16_t data;

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(ledRing, TOTAL_LEDS_INNER_RING + TOTAL_LEDS_OUTER_RING);

  Serial.begin(9600);
  Serial.println("Serial setup complete.");
}

// The fill_rainbow call doesn't support brightness levels.
void rainbow_wave(uint8_t thisSpeed, uint8_t deltaHue) {

  // Simple rainbow wave
  // uint8_t thisHue = beatsin8(thisSpeed,0,255);
  // Simple rainbow march
   uint8_t thisHue = beat8(thisSpeed,255);
    
   fill_rainbow(ledRing, TOTAL_LEDS, thisHue, deltaHue);
}

void loop() {
  // Read data from the IR sensor
  data = analogRead(A5);
  Serial.println(data);
  delay(100);

  // Trigger the lights on the ring
  // if the data value within range
  if(data < 100) {
    fill_solid(ledRing, TOTAL_LEDS, CRGB::Black);
    for(int i = 0; i < TOTAL_LEDS_OUTER_RING; i++){
      ledRing[i] = CRGB::Green;
      FastLED.show();
      delay(50);
    }
    fill_solid(ledRing, TOTAL_LEDS, CRGB::Green);
    FastLED.show();
    delay(100);
    fill_solid(ledRing, TOTAL_LEDS, CRGB::Black);
    FastLED.show();
    delay(100);
    fill_solid(ledRing, TOTAL_LEDS, CRGB::Green);
    FastLED.show();
    delay(500);

    // for(int i = 0; i < TOTAL_LEDS; i++) {
    //   ledRing[i] = CRGB::Black;
    //   FastLED.show();
    //   delay(50);
    // }
    // fill_solid(ledRing, TOTAL_LEDS_OUTER_RING, CRGB::Green);
    // fill_solid(ledInnerRing, TOTAL_LEDS_INNER_RING, CRGB::Black);
    // FastLED.show();
  } else {
    rainbow_wave(10, 10);
    FastLED.show();
  }
}