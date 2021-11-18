// includes
#include <i2c_driver_wire.h>
#include <OSCMessage.h>
#include <OSCBundle.h>

// constants
#define WIRE_ADDR 0x2D


void setup() {
  // put your setup code here, to run once:
  
  initAudio();
  initOSC();
}


void loop() {
  // for monitoring audio memory usage; uncomment if necessary
  monitorBlocks();
}
