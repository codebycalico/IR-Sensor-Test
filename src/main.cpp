#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 2
#define TOTAL_LEDS_OUTER_RING 12
#define TOTAL_LEDS_INNER_RING 18

CRGBArray <TOTAL_LEDS_OUTER_RING + TOTAL_LEDS_INNER_RING> ledStrip;
uint16_t data;

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(ledStrip, TOTAL_LEDS_INNER_RING + TOTAL_LEDS_OUTER_RING);

  Serial.begin(9600);
  Serial.println("Serial setup complete.");
}

void loop() {
  // Read data from the IR sensor
  data = analogRead(A5);
  Serial.println(data);
  delay(100);

  // Trigger the lights on the ring
  // if the data value within range
  if(data < 100) {
    fill_solid(ledStrip, TOTAL_LEDS_OUTER_RING, CRGB::Green);
    FastLED.show();
  }
}