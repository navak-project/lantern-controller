// includes
#include <Audio.h>
#include <i2c_driver_wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <OSCMessage.h>
#include <OSCBundle.h>

// GUItool: begin automatically generated code
AudioSynthWavetable      heartbeat;     //xy=249,316
AudioPlaySdWav           lanternLoop;     //xy=250,162
AudioFilterStateVariable filter1;        //xy=429,325
AudioPlaySdWav           lanternEvents;     //xy=445,84
AudioEffectFade          lanternLoopFade;          //xy=445,156
AudioMixer4              mixer1;         //xy=657,208
AudioOutputI2S           i2s1;           //xy=832,207
AudioConnection          patchCord1(heartbeat, 0, filter1, 0);
AudioConnection          patchCord2(lanternLoop, 0, lanternLoopFade, 0);
AudioConnection          patchCord3(filter1, 0, mixer1, 2);
AudioConnection          patchCord4(lanternEvents, 0, mixer1, 0);
AudioConnection          patchCord5(lanternLoopFade, 0, mixer1, 1);
AudioConnection          patchCord6(mixer1, 0, i2s1, 0);
AudioConnection          patchCord7(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=500,573
// GUItool: end automatically generated code


// constants
#define WIRE_ADDR        0x2D
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14
// properties
int lanternID = 0;


void setup() {
  // init Teensy Audio + SD
  initAudio();
  initSD();

  // init OSC thru Wire
  initOSC();
}


void loop() {
  // for monitoring audio memory usage; uncomment if necessary
  monitorBlocks();
}
