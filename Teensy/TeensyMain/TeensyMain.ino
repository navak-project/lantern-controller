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
AudioSynthWavetable      hbSynth4;  //xy=125.5,346
AudioSynthWavetable      hbSynth1;      //xy=126.5,224
AudioSynthWaveform       sineMod1;      //xy=146,434
AudioSynthWaveform       sineMod2; //xy=146,482
AudioSynthWaveform       sineMod3; //xy=146,528
AudioMixer4              hbWavetableMixer;         //xy=338.5,282
AudioSynthNoiseWhite     noise1;         //xy=379,593
AudioSynthWaveformModulated sineRing3; //xy=384,534
AudioSynthWaveformModulated sineRing1;   //xy=386,440
AudioSynthWaveformModulated sineRing2;  //xy=386,488
AudioEffectMultiply      ringMod4; //xy=597,590
AudioEffectMultiply      ringMod1;      //xy=600,441
AudioEffectMultiply      ringMod3; //xy=600,540
AudioEffectMultiply      ringMod2; //xy=601,490
AudioMixer4              hbStaticMixer; //xy=794,514
AudioEffectFade          hbPureFader;          //xy=978,294
AudioEffectFade          hbStaticFader; //xy=978,337
AudioFilterBiquad        staticFilter;        //xy=986,513
AudioPlaySdWav           lanternLoop;    //xy=1030,210
AudioMixer4              hbMixer;         //xy=1173,324
AudioEffectFade          lanternLoopFade; //xy=1226,203
AudioPlaySdWav           lanternEvents;  //xy=1227,134
AudioMixer4              mainMixer;         //xy=1479,214
AudioOutputI2S           i2sOut;           //xy=1654,213
AudioConnection          patchCord1(hbSynth2, 0, hbWavetableMixer, 1);
AudioConnection          patchCord2(hbSynth3, 0, hbWavetableMixer, 2);
AudioConnection          patchCord3(hbSynth4, 0, hbWavetableMixer, 3);
AudioConnection          patchCord4(hbSynth1, 0, hbWavetableMixer, 0);
AudioConnection          patchCord5(sineMod1, 0, sineRing1, 0);
AudioConnection          patchCord6(sineMod2, 0, sineRing2, 0);
AudioConnection          patchCord7(sineMod3, 0, sineRing3, 0);
AudioConnection          patchCord8(hbWavetableMixer, 0, ringMod1, 0);
AudioConnection          patchCord9(hbWavetableMixer, 0, ringMod2, 0);
AudioConnection          patchCord10(hbWavetableMixer, 0, ringMod3, 1);
AudioConnection          patchCord11(hbWavetableMixer, 0, ringMod4, 0);
AudioConnection          patchCord12(hbWavetableMixer, fade1);
AudioConnection          patchCord13(noise1, 0, ringMod4, 1);
AudioConnection          patchCord14(sineRing3, 0, ringMod3, 0);
AudioConnection          patchCord15(sineRing1, 0, ringMod1, 1);
AudioConnection          patchCord16(sineRing2, 0, ringMod2, 1);
AudioConnection          patchCord17(ringMod4, 0, hbStaticMixer, 3);
AudioConnection          patchCord18(ringMod1, 0, hbStaticMixer, 0);
AudioConnection          patchCord19(ringMod3, 0, hbStaticMixer, 2);
AudioConnection          patchCord20(ringMod2, 0, hbStaticMixer, 1);
AudioConnection          patchCord21(hbStaticMixer, staticFilter);
AudioConnection          patchCord22(fade1, 0, hbMixer, 0);
AudioConnection          patchCord23(fade2, 0, hbMixer, 1);
AudioConnection          patchCord24(staticFilter, fade2);
AudioConnection          patchCord25(lanternLoop, 0, lanternLoopFade, 0);
AudioConnection          patchCord26(hbMixer, 0, mainMixer, 2);
AudioConnection          patchCord27(lanternLoopFade, 0, mainMixer, 1);
AudioConnection          patchCord28(lanternEvents, 0, mainMixer, 0);
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
  testSequence();
}
