#include <Wire.h>
#include <Arduino.h>
#include <Packetizer.h>

Packetizer::Packer packer(10);

void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  send();
}

void loop() {
}

void send(){
  Wire.beginTransmission(0x01); // transmit to device #8
  packer.pack(10, 255, 255, 0);
  Wire.write(packer.data(), packer.size());
  Wire.endTransmission(); // stop transmitting
  delay(500);
  packer.init(10);
  Wire.beginTransmission(0x02); // transmit to device #8
  packer.pack(11, 255, 0, 255);
  Wire.write(packer.data(), packer.size());
  Wire.endTransmission(); // stop transmitting
  delay(500);
}