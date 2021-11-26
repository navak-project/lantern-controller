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

// instruments
#include "flute_01_samples.h"

// GUItool: begin automatically generated code
AudioPlaySdWav           lanternLoop;    //xy=378,222
AudioSynthWavetable      hbSynth1;      //xy=380,302
AudioEffectFade          lanternLoopFade; //xy=574,215
AudioPlaySdWav           lanternEvents;  //xy=575,146
AudioMixer4              hbMixer;         //xy=603,320
AudioMixer4              mainMixer;         //xy=827,226
AudioOutputI2S           i2sOut;           //xy=1002,225
AudioConnection          patchCord1(lanternLoop, 0, lanternLoopFade, 0);
AudioConnection          patchCord2(hbSynth1, 0, hbMixer, 0);
AudioConnection          patchCord3(lanternLoopFade, 0, mainMixer, 1);
AudioConnection          patchCord4(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord5(hbMixer, 0, mainMixer, 2);
AudioConnection          patchCord6(mainMixer, 0, i2sOut, 0);
AudioConnection          patchCord7(mainMixer, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=459,571
// GUItool: end automatically generated code

// constants
#define WIRE_ADDR        0x2D
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// properties

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
  monitorBlocks();

  // lantern loop manager
  updateLanternLoop();

  // heartbeat manager
  updateHeartbeat();

  // test sequence
  testSequence();
}
