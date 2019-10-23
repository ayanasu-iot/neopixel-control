#include <Wire.h>
#include <FastLED.h>
#include <Arduino.h>
#include <Packetizer.h>

Packetizer::Unpacker unpacker;

#define LED_CHAINS 35
CRGB leds[LED_CHAINS];
#define PIN 6

void setup() {
  Wire.begin(0x03);             // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  FastLED.addLeds<WS2811, PIN, GRB>(leds, LED_CHAINS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(16);

  uint8_t index = 10;
  unpacker.subscribe(index, callback);
}

void callback(const uint8_t* data, uint8_t size){
  Serial.print("Pixel:");
  Serial.println((int)data[1]);
  Serial.print("R:");
  Serial.println((int)data[1]);
  Serial.print("G:");
  Serial.println((int)data[2]);
  Serial.print("B:");
  Serial.println((int)data[3]);
  setPixel((int)data[0], (int)data[1], (int)data[2], (int)data[3]);
  showStrip();
}

void loop() {
}

void receiveEvent(int howMany) {
  while (const int size = Wire.available()){
    uint8_t data[size];
    Wire.readBytes((char*)data, size);
    unpacker.feed(data, size);
    }
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
