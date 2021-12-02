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
AudioSynthWavetable      hbSynth2;       //xy=647,286
AudioSynthWavetable      hbSynth3;       //xy=648,327
AudioSynthWavetable      hbSynth4;       //xy=648,367
AudioSynthWavetable      hbSynth1;       //xy=649,244
AudioSynthWaveformSine   sineMod;        //xy=784,507
AudioMixer4              hbWavetableMixer; //xy=861,302
AudioSynthWaveform       noiseFiltMod;   //xy=899,644
AudioSynthNoiseWhite     noiseMod;       //xy=902,598
AudioEffectMultiply      ringMod1;       //xy=968,500
AudioFilterStateVariable noiseBP;        //xy=1055,604
AudioFilterBiquad        ringModLP;      //xy=1154,497
AudioPlaySdRaw           lanternLoop;    //xy=1179,251
AudioEffectMultiply      ringMod2;       //xy=1208,550
AudioSynthWaveformSine   sineAM;         //xy=1212,607
AudioSynthWaveformDc     loopAttenDC;    //xy=1325,141
AudioEffectFade          lanternLoopFade; //xy=1342,245
AudioEffectMultiply      noiseAM;        //xy=1365,582
AudioEffectMultiply      loopAtten;      //xy=1471,62
AudioEffectFade          pureFader;      //xy=1501,314
AudioEffectFade          staticFader;    //xy=1501,357
AudioFilterStateVariable preDlyFilter;   //xy=1501,588
AudioSynthWaveformDc     loopFilterDC;   //xy=1524,138
AudioMixer4              staticMixer;    //xy=1550,457
AudioFilterStateVariable lanternLoopFilter; //xy=1650,50
AudioPlaySdWav           lanternEvents;  //xy=1673,132
AudioMixer4              hbMixer;        //xy=1696,344
AudioEffectDelay         noiseDly;       //xy=1753,619
AudioMixer4              preDlyMixer;    //xy=1754,733
AudioMixer4              mainMixer;      //xy=2002,234
AudioOutputI2S           i2sOut;         //xy=2177,233
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
AudioConnection          patchCord14(lanternLoop, 0, lanternLoopFade, 0);
AudioConnection          patchCord15(ringMod2, 0, noiseAM, 0);
AudioConnection          patchCord16(sineAM, 0, noiseAM, 1);
AudioConnection          patchCord17(loopAttenDC, 0, loopAtten, 0);
AudioConnection          patchCord18(lanternLoopFade, 0, loopAtten, 1);
AudioConnection          patchCord19(lanternLoopFade, 0, mainMixer, 1);
AudioConnection          patchCord20(noiseAM, 0, preDlyFilter, 0);
AudioConnection          patchCord21(loopAtten, 0, lanternLoopFilter, 0);
AudioConnection          patchCord22(pureFader, 0, hbMixer, 0);
AudioConnection          patchCord23(staticFader, 0, hbMixer, 1);
AudioConnection          patchCord24(preDlyFilter, 0, preDlyMixer, 0);
AudioConnection          patchCord25(preDlyFilter, 1, staticMixer, 0);
AudioConnection          patchCord26(loopFilterDC, 0, lanternLoopFilter, 1);
AudioConnection          patchCord27(staticMixer, staticFader);
AudioConnection          patchCord28(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord29(hbMixer, 0, mainMixer, 2);
AudioConnection          patchCord30(noiseDly, 0, preDlyMixer, 1);
AudioConnection          patchCord31(noiseDly, 0, staticMixer, 1);
AudioConnection          patchCord32(preDlyMixer, noiseDly);
AudioConnection          patchCord33(mainMixer, 0, i2sOut, 0);
AudioConnection          patchCord34(mainMixer, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1167,58
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

  lanternLoop.play("lantern_loops/lantern_loop_0.raw", true);
}


void loop() {
  // for monitoring audio memory usage; uncomment if necessary
  //monitorBlocks();

  // heartbeat manager
  updateHeartbeat();

  // test sequence
  //testSequence();

  delayMicroseconds(100);
}
