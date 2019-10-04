#include <Wire.h>
#include <Arduino.h>
#include <Packetizer.h>

Packetizer::Packer packer;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  packer.pack(100, 100, 100);
  Wire.write(packer.data);
  Wire.endTransmission(); // stop transmitting

  x++;
  delay(500);
}
