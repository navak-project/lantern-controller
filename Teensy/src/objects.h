#ifndef T4_OBJECTS
#define T4_OBJECTS


// instruments
#include "instruments/hb_part1_samples.h"
#include "instruments/hb_part2_samples.h"
#include "instruments/hb_part3_samples.h"
#include "instruments/hb_part4_samples.h"

// GUItool: begin automatically generated code
AudioSynthWavetable      hbSynth2;       //xy=118,290
AudioSynthWavetable      hbSynth3;       //xy=119,331
AudioSynthWavetable      hbSynth4;       //xy=119,371
AudioSynthWavetable      hbSynth1;       //xy=120,248
AudioMixer4              hbWavetableMixer; //xy=332,306
AudioSynthWaveform       noiseFiltMod;   //xy=366,705
AudioSynthNoiseWhite     noiseMod;       //xy=369,659
AudioSynthWaveformSine   sineMod;        //xy=487,503
AudioFilterStateVariable noiseBP;        //xy=522,665
AudioSynthNoiseWhite     hum;         //xy=594,86
AudioPlaySdRaw           lanternLoop;    //xy=605,133
AudioEffectMultiply      ringMod1;       //xy=671,496
AudioSynthWaveformSine   sineAM;         //xy=672,658
AudioEffectMultiply      ringMod2;       //xy=675,611
AudioMixer4              loopHumMix;         //xy=765,119
AudioFilterBiquad        ringModLP;      //xy=857,491
AudioEffectMultiply      noiseAM;        //xy=862,631
AudioSynthWaveformDc     loopAttenDC;    //xy=953,20
AudioEffectFade          lanternLoopFade; //xy=963,115
AudioFilterStateVariable preDlyFilter;   //xy=1049,637
AudioEffectMultiply      loopAtten;      //xy=1174,58
AudioSynthWaveformDc     loopFilterDC;   //xy=1179,96
AudioMixer4              staticMixer;    //xy=1254,487
AudioFilterStateVariable lanternLoopFilter; //xy=1371,76
AudioEffectFade          pureFader;      //xy=1433,316
AudioEffectFade          staticFader;    //xy=1434,385
AudioMixer4              hbMixer;        //xy=1620,336
AudioEffectFreeverb      hbReverb;      //xy=1745,420
AudioPlaySdRaw           lanternEvents;     //xy=1782,186
AudioPlaySdRaw           narrationPlayer;     //xy=1786,246
AudioMixer4              hbReverbMixer;         //xy=1909,321
AudioMixer4              mainMixer;      //xy=2038,211
AudioAmplifier           ampOut;           //xy=2198,211
AudioOutputI2S           i2sOut;         //xy=2388,208
AudioConnection          patchCord1(hbSynth2, 0, hbWavetableMixer, 1);
AudioConnection          patchCord2(hbSynth3, 0, hbWavetableMixer, 2);
AudioConnection          patchCord3(hbSynth4, 0, hbWavetableMixer, 3);
AudioConnection          patchCord4(hbSynth1, 0, hbWavetableMixer, 0);
AudioConnection          patchCord5(hbWavetableMixer, pureFader);
AudioConnection          patchCord6(hbWavetableMixer, 0, ringMod1, 0);
AudioConnection          patchCord7(hbWavetableMixer, 0, ringMod2, 0);
AudioConnection          patchCord8(noiseFiltMod, 0, noiseBP, 1);
AudioConnection          patchCord9(noiseMod, 0, noiseBP, 0);
AudioConnection          patchCord10(sineMod, 0, ringMod1, 1);
AudioConnection          patchCord11(noiseBP, 2, ringMod2, 1);
AudioConnection          patchCord12(hum, 0, loopHumMix, 0);
AudioConnection          patchCord13(lanternLoop, 0, loopHumMix, 1);
AudioConnection          patchCord14(ringMod1, ringModLP);
AudioConnection          patchCord15(sineAM, 0, noiseAM, 1);
AudioConnection          patchCord16(ringMod2, 0, noiseAM, 0);
AudioConnection          patchCord17(loopHumMix, lanternLoopFade);
AudioConnection          patchCord18(ringModLP, 0, staticMixer, 2);
AudioConnection          patchCord19(noiseAM, 0, preDlyFilter, 0);
AudioConnection          patchCord20(loopAttenDC, 0, loopAtten, 0);
AudioConnection          patchCord21(lanternLoopFade, 0, loopAtten, 1);
AudioConnection          patchCord22(preDlyFilter, 1, staticMixer, 0);
AudioConnection          patchCord23(loopAtten, 0, lanternLoopFilter, 0);
AudioConnection          patchCord24(loopFilterDC, 0, lanternLoopFilter, 1);
AudioConnection          patchCord25(staticMixer, staticFader);
AudioConnection          patchCord26(lanternLoopFilter, 0, mainMixer, 1);
AudioConnection          patchCord27(pureFader, 0, hbMixer, 0);
AudioConnection          patchCord28(staticFader, 0, hbMixer, 1);
AudioConnection          patchCord29(hbMixer, hbReverb);
AudioConnection          patchCord30(hbMixer, 0, hbReverbMixer, 0);
AudioConnection          patchCord31(hbReverb, 0, hbReverbMixer, 1);
AudioConnection          patchCord32(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord33(narrationPlayer, 0, mainMixer, 3);
AudioConnection          patchCord34(hbReverbMixer, 0, mainMixer, 2);
AudioConnection          patchCord35(mainMixer, ampOut);
AudioConnection          patchCord36(ampOut, 0, i2sOut, 0);
AudioConnection          patchCord37(ampOut, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=761,256
// GUItool: end automatically generated code



// constants
#define WIRE_ADDR        0x2D
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// properties
String lanternID;
int lanternIndex;


#endif