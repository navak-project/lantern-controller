#include <i2c_driver_wire.h>
#include <OSCMessage.h>
#include <OSCBundle.h>

void setup() {
  Wire1.begin(0x2D);
  Wire1.onReceive(receiveOSC);

  Serial.begin(112500);
}

void loop() {
  // nothing happens here
  delay(100);
}

void receiveOSC(int a) {
  OSCBundle bundleIN;

  while (Wire1.available()) {
    bundleIN.fill(Wire1.read());
  }

  if (!bundleIN.hasError()) {
    bundleIN.dispatch("/audio/test", audioTest);
  }
}

void audioTest(OSCMessage &msg) {
  Serial.println(msg.getInt(0));
}
