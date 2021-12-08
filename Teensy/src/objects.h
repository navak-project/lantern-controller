#ifndef T4_OBJECTS
#define T4_OBJECTS


// instruments
#include "instruments/hb_part1_samples.h"
#include "instruments/hb_part2_samples.h"
#include "instruments/hb_part3_samples.h"
#include "instruments/hb_part4_samples.h"

// GUItool: begin automatically generated code
AudioSynthWavetable      hbSynth2;       //xy=350,282
AudioSynthWavetable      hbSynth3;       //xy=351,323
AudioSynthWavetable      hbSynth4;       //xy=351,363
AudioSynthWavetable      hbSynth1;       //xy=352,240
AudioSynthWaveformSine   sineMod;        //xy=487,503
AudioMixer4              hbWavetableMixer; //xy=564,298
AudioSynthWaveform       noiseFiltMod;   //xy=602,640
AudioSynthNoiseWhite     noiseMod;       //xy=605,594
AudioEffectMultiply      ringMod1;       //xy=671,496
AudioFilterStateVariable noiseBP;        //xy=758,600
AudioFilterBiquad        ringModLP;      //xy=857,493
AudioPlaySdRaw           lanternLoop;    //xy=870,238
AudioSynthWaveformSine   sineAM;         //xy=908,593
AudioEffectMultiply      ringMod2;       //xy=911,546
AudioSynthWaveformDc     loopAttenDC;    //xy=1028,137
AudioEffectFade          lanternLoopFade; //xy=1045,241
AudioEffectMultiply      noiseAM;        //xy=1068,578
AudioEffectMultiply      loopAtten;      //xy=1174,58
AudioEffectFade          pureFader;      //xy=1204,310
AudioEffectFade          staticFader;    //xy=1204,353
AudioFilterStateVariable preDlyFilter;   //xy=1204,584
AudioSynthWaveformDc     loopFilterDC;   //xy=1227,134
AudioFilterStateVariable lanternLoopFilter; //xy=1353,46
AudioMixer4              staticMixer;    //xy=1366,461
AudioMixer4              hbMixer;        //xy=1399,340
AudioPlaySdRaw           lanternEvents;     //xy=1406,177
AudioMixer4              mainMixer;      //xy=1705,230
AudioAmplifier           ampOut;           //xy=1865,230
AudioOutputI2S           i2sOut;         //xy=2055,227
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
AudioConnection          patchCord14(lanternLoop, lanternLoopFade);
AudioConnection          patchCord15(sineAM, 0, noiseAM, 1);
AudioConnection          patchCord16(ringMod2, 0, noiseAM, 0);
AudioConnection          patchCord17(loopAttenDC, 0, loopAtten, 0);
AudioConnection          patchCord18(lanternLoopFade, 0, loopAtten, 1);
AudioConnection          patchCord19(lanternLoopFade, 0, mainMixer, 1);
AudioConnection          patchCord20(noiseAM, 0, preDlyFilter, 0);
AudioConnection          patchCord21(loopAtten, 0, lanternLoopFilter, 0);
AudioConnection          patchCord22(pureFader, 0, hbMixer, 0);
AudioConnection          patchCord23(staticFader, 0, hbMixer, 1);
AudioConnection          patchCord24(preDlyFilter, 1, staticMixer, 0);
AudioConnection          patchCord25(loopFilterDC, 0, lanternLoopFilter, 1);
AudioConnection          patchCord26(staticMixer, staticFader);
AudioConnection          patchCord27(hbMixer, 0, mainMixer, 2);
AudioConnection          patchCord28(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord29(mainMixer, ampOut);
AudioConnection          patchCord30(ampOut, 0, i2sOut, 0);
AudioConnection          patchCord31(ampOut, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=701,128
// GUItool: end automatically generated code


// constants
#define WIRE_ADDR        0x2D
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14


#endif