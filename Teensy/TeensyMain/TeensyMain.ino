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
#include "hb_part1_samples.h"
#include "hb_part2_samples.h"
#include "hb_part3_samples.h"
#include "hb_part4_samples.h"

// GUItool: begin automatically generated code
AudioSynthWavetable      hbSynth2; //xy=124.5,266
AudioSynthWavetable      hbSynth3; //xy=125.5,307
AudioSynthWavetable      hbSynth4;  //xy=125.5,347
AudioSynthWavetable      hbSynth1;      //xy=126.5,224
AudioSynthWaveformSine   sineMod;          //xy=261,487
AudioMixer4              hbWavetableMixer;         //xy=338.5,282
AudioSynthWaveform       noiseFiltMod;      //xy=376,624
AudioSynthNoiseWhite     noiseMod;         //xy=379,578
AudioEffectMultiply      ringMod1;      //xy=445,480
AudioFilterStateVariable noiseBP;        //xy=532,584
AudioFilterBiquad        ringModLP;        //xy=631,477
AudioEffectMultiply      ringMod2;      //xy=685,530
AudioSynthWaveformSine   sineAM;          //xy=689,587
AudioMixer4              staticMixer;         //xy=805,411
AudioEffectMultiply      noiseAM;      //xy=842,562
AudioEffectFade          pureFader;          //xy=978,294
AudioEffectFade          staticFader; //xy=978,337
AudioFilterStateVariable preDlyFilter;        //xy=978,568
AudioPlaySdWav           lanternLoop;    //xy=1030,210
AudioMixer4              preDlyMixer;         //xy=1148,631
AudioMixer4              hbMixer;         //xy=1173,324
AudioEffectFade          lanternLoopFade; //xy=1226,203
AudioPlaySdWav           lanternEvents;  //xy=1227,134
AudioEffectDelay         noiseDly;         //xy=1299,649
AudioMixer4              mainMixer;         //xy=1479,214
AudioOutputI2S           i2sOut;           //xy=1654,213
AudioConnection          patchCord1(hbSynth2, 0, hbWavetableMixer, 1);
AudioConnection          patchCord2(hbSynth3, 0, hbWavetableMixer, 2);
AudioConnection          patchCord3(hbSynth4, 0, hbWavetableMixer, 3);
AudioConnection          patchCord4(hbSynth1, 0, hbWavetableMixer, 0);
AudioConnection          patchCord5(sineMod, 0, ringMod1, 1);
AudioConnection          patchCord6(hbWavetableMixer, pureFader);
AudioConnection          patchCord7(hbWavetableMixer, 0, ringMod1, 0);
AudioConnection          patchCord8(hbWavetableMixer, 0, ringMod2, 0);
AudioConnection          patchCord9(noiseFiltMod, 0, noiseBP, 1);
AudioConnection          patchCord10(noiseMod, 0, noiseBP, 0);
AudioConnection          patchCord11(ringMod1, ringModLP);
AudioConnection          patchCord12(noiseBP, 2, ringMod2, 1);
AudioConnection          patchCord13(ringModLP, 0, staticMixer, 2);
AudioConnection          patchCord14(ringMod2, 0, noiseAM, 0);
AudioConnection          patchCord15(sineAM, 0, noiseAM, 1);
AudioConnection          patchCord16(staticMixer, staticFader);
AudioConnection          patchCord17(noiseAM, 0, preDlyFilter, 0);
AudioConnection          patchCord18(pureFader, 0, hbMixer, 0);
AudioConnection          patchCord19(staticFader, 0, hbMixer, 1);
AudioConnection          patchCord20(preDlyFilter, 0, preDlyMixer, 0);
AudioConnection          patchCord21(preDlyFilter, 1, staticMixer, 0);
AudioConnection          patchCord22(lanternLoop, 0, lanternLoopFade, 0);
AudioConnection          patchCord23(preDlyMixer, noiseDly);
AudioConnection          patchCord24(hbMixer, 0, mainMixer, 2);
AudioConnection          patchCord25(lanternLoopFade, 0, mainMixer, 1);
AudioConnection          patchCord26(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord27(noiseDly, 0, preDlyMixer, 1);
AudioConnection          patchCord28(noiseDly, 0, staticMixer, 1);
AudioConnection          patchCord29(mainMixer, 0, i2sOut, 0);
AudioConnection          patchCord30(mainMixer, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=601,53
// GUItool: end automatically generated code


// constants
#define WIRE_ADDR        0x2D
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

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
  //monitorBlocks();

  // lantern loop manager
  updateLanternLoop();

  // heartbeat manager
  updateHeartbeat();

  // test sequence
  //testSequence();
}
