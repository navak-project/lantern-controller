// includes
// FUN FACT: using this Wire library will require you to change
// every single instance of Wire.h in the entirety of Teensyduino's code :o)
#include <Audio.h>
#include <i2c_driver_wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <OSCMessage.h>
#include <OSCBundle.h>


#include "objects.h"
#include "audio_manager.h"
#include "lantern_events.h"
#include "organique_events.h"
#include "heartbeat_events.h"
#include "osc_manager.h"


void testSequence();


void setup() {
  // init Teensy Audio + SD
  initAudio();
  initSD();

  // init OSC thru Wire
  initOSC();

  // init props
  initLantern();
  initHeartbeat();
}


void loop() {
  // for monitoring audio memory usage; uncomment if necessary
  // monitorBlocks();

  // heartbeat manager
  updateHeartbeat();

  // test sequence
  // testSequence();

  delayMicroseconds(10);
}



elapsedMillis testSeqTimer;
bool ignited = false;
bool extinguished = false;

void testSequence() {
  OSCMessage dummy;

  if (testSeqTimer > 2000 && !ignited) {
    igniteLantern(dummy);
    ignited = true;
  }

  if (testSeqTimer > 27000 && !extinguished) {
    extinguishLantern(dummy);
    extinguished = true;
  }
}
