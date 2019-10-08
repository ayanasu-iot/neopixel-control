#include <Wire.h>
#include <Arduino.h>
#include <Packetizer.h>

Packetizer::Packer packer(10);

#define LED_CHAINS 35

void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  delay(100);
}

void loop() {
  send();
}

void send(){
  for (int index = 0; index < LED_CHAINS; index++){
    //0x01
    packer.init(10);
    Wire.beginTransmission(0x01); // transmit to device #1
    packer.pack(index, 255, 0, 255);
    Wire.write(packer.data(), packer.size());
    delay(10);
    packer.init(10);
    packer.pack(index, 0, 0, 0);
    Wire.write(packer.data(), packer.size());
    Wire.endTransmission(); // stop transmitting
    //0x02
    packer.init(10);
    Wire.beginTransmission(0x02); // transmit to device #1
    packer.pack(index+1, 255, 0, 255);
    Wire.write(packer.data(), packer.size());
    delay(10);
    packer.init(10);
    packer.pack(index+1, 0, 0, 0);
    Wire.write(packer.data(), packer.size());
    Wire.endTransmission(); // stop transmitting
    //0x03
    packer.init(10);
    Wire.beginTransmission(0x03); // transmit to device #3
    packer.pack(index+2, 255, 0, 255);
    Wire.write(packer.data(), packer.size());
    delay(10);
    packer.init(10);
    packer.pack(index+2, 0, 0, 0);
    Wire.write(packer.data(), packer.size());
    Wire.endTransmission(); // stop transmitting
    //0x04
    packer.init(10);
    Wire.beginTransmission(0x04); // transmit to device #4
    packer.pack(index+3, 255, 0, 255);
    Wire.write(packer.data(), packer.size());
    delay(10);
    packer.init(10);
    packer.pack(index+3, 0, 0, 0);
    Wire.write(packer.data(), packer.size());
    Wire.endTransmission(); // stop transmitting
    //0x05
    packer.init(10);
    Wire.beginTransmission(0x05); // transmit to device #5
    packer.pack(index+4, 255, 0, 255);
    Wire.write(packer.data(), packer.size());
    delay(10);
    packer.init(10);
    packer.pack(index+4, 0, 0, 0);
    Wire.write(packer.data(), packer.size());
    Wire.endTransmission(); // stop transmitting
  }
}