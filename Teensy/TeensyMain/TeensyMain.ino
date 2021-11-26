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

// GUItool: begin automatically generated code
AudioSynthWaveformDc     hbFilterCtrl;            //xy=331,370
AudioSynthWavetable      hbSynth1;      //xy=333,310
AudioPlaySdWav           lanternLoop;    //xy=434,170
AudioFilterStateVariable hbFilter;        //xy=565,316
AudioEffectFade          lanternLoopFade; //xy=633,168
AudioPlaySdWav           lanternEvents;  //xy=634,99
AudioMixer4              hbMixer;         //xy=824,323
AudioMixer4              mainMixer;         //xy=1048,229
AudioOutputI2S           i2sOut;           //xy=1223,228
AudioConnection          patchCord1(hbFilterCtrl, 0, hbFilter, 1);
AudioConnection          patchCord2(hbSynth1, 0, hbFilter, 0);
AudioConnection          patchCord3(lanternLoop, 0, lanternLoopFade, 0);
AudioConnection          patchCord4(hbFilter, 0, hbMixer, 0);
AudioConnection          patchCord5(lanternLoopFade, 0, mainMixer, 1);
AudioConnection          patchCord6(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord7(hbMixer, 0, mainMixer, 2);
AudioConnection          patchCord8(mainMixer, 0, i2sOut, 0);
AudioConnection          patchCord9(mainMixer, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=680,574
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
}
