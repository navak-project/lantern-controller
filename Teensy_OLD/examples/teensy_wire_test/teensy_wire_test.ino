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
  // define OSC bundle
  OSCBundle bundleIN;

  // decode incoming OSC message
  while (Wire1.available()) {
    bundleIN.fill(Wire1.read());
  }

  // list of callbacks
  if (!bundleIN.hasError()) {
    bundleIN.dispatch("/audio/test", audioTest);
    // bundleIN.dispatch("/audio/test2", audioTest2);
    // bundleIN.dispatch("/audio/test3", audioTest3);
  }
}

// callback test (prints out first msg argument)
void audioTest(OSCMessage &msg) {
  Serial.println(msg.getInt(0));
}
