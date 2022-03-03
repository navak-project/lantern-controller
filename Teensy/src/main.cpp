// includes
#include <Audio.h>
#include <AsyncDelay.h>
// FUN FACT: using this Wire library will require you to change
// every single instance of Wire.h in the entirety of Teensyduino's code :o)
// (you probably won't need to if you know how to replace the library)
#include <i2c_driver_wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <map>


#include "objects.h"
#include "audio_manager.h"
#include "lantern_events.h"
#include "organique_events.h"
#include "heartbeat_events.h"
#include "narr_events.h"
#include "osc_manager.h"


// function headers
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

  // loop managers
  // updateVolumePot();
  updateHeartbeat();
  updateLanternEvents();

  // test sequence
  // uncomment if you want to test a predetermined chain of events from the moment the Teensy is powered on
  // testSequence();

  // complimentary delay :o)
  delayMicroseconds(10);
}


// THIS SECTION IS FOR TESTING!
elapsedMillis testSeqTimer;
bool ignited = false;
bool extinguished = false;

void testSequence() {
  OSCMessage dummy;

  // after 2 seconds:
  if (testSeqTimer > 2000 && !ignited) {
    // ignite
    igniteLantern(dummy);
    ignited = true;
  }

  // after 27 seconds:
  if (testSeqTimer > 27000 && !extinguished) {
    // extinguish
    extinguishLantern(dummy);
    extinguished = true;
  }
}
