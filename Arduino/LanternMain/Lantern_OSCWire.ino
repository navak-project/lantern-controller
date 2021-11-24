void InitWire() {
  Wire.begin();
}

void AudioTest() {
  // construct message
  OSCMessage msg("/audio/test");
  msg.add(1);
  // send
  SendToTeensy(msg);
}

// through I2C communication
void SendToTeensy(OSCMessage &msg) {
  Serial.println("Sent Message to Teensy");
  Wire.beginTransmission(0x2D);
  msg.send(Wire);
  Wire.endTransmission();
}
