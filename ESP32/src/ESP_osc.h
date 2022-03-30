#ifndef __ESP_OSC_H__
#define __ESP_OSC_H__

#include <Wire.h>
#include "global.h"

void InitWire() {
  Wire.begin(21, 22);
}

// through I2C communication
void SendToTeensy(OSCMessage &msg) {
  Wire.beginTransmission(0x2D);
  msg.send(Wire);
  Wire.endTransmission();
  Serial.println("Sent Message to Teensy");
}

#endif // __ESP_OSC_H__