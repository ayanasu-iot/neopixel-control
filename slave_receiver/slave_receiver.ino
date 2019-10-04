#include <Wire.h>
#include <FastLED.h>
#include <Arduino.h>

#define LED_CHAINS 35
CRGB leds[LED_CHAINS];
#define PIN 6

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  FastLED.addLeds<WS2811, PIN, GRB>(leds, LED_CHAINS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(16);
}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < LED_CHAINS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   FastLED.show();
 #endif
}