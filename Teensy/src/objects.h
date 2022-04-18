#ifndef T4_OBJECTS
#define T4_OBJECTS


// instruments
#include "instruments/hb_part1_samples.h"
#include "instruments/hb_part2_samples.h"
#include "instruments/hb_part3_samples.h"
#include "instruments/hb_part4_samples.h"

// GUItool: begin automatically generated code
AudioSynthWavetable      hbSynth2;       //xy=114,649
AudioSynthWavetable      hbSynth3;       //xy=115,690
AudioSynthWavetable      hbSynth4;       //xy=115,738
AudioSynthWavetable      hbSynth1;       //xy=116,607
AudioMixer4              hbWavetableMixer; //xy=328,665
AudioSynthWaveform       noiseFiltMod;   //xy=362,1064
AudioSynthNoiseWhite     noiseMod;       //xy=365,1018
AudioSynthWaveformSine   sineMod;        //xy=483,862
AudioFilterStateVariable noiseBP;        //xy=518,1024
AudioPlaySdRaw           fireRaw;        //xy=575,175
AudioPlaySdRaw           wooshRaw;       //xy=586,320
AudioSynthNoiseWhite     hum;            //xy=587,247
AudioEffectMultiply      ringMod1;       //xy=667,855
AudioSynthWaveformSine   sineAM;         //xy=668,1017
AudioEffectMultiply      ringMod2;       //xy=671,970
AudioFilterBiquad        ringModLP;      //xy=853,850
AudioEffectMultiply      noiseAM;        //xy=858,990
AudioMixer4              fireHumMix;     //xy=890,193
AudioMixer4              wooshHumMix;    //xy=895,306
AudioSynthNoiseWhite     rmb_noise;      //xy=947,545
AudioSynthWaveformDc     rmb_offset;            //xy=954,588
AudioFilterStateVariable preDlyFilter;   //xy=1045,996
AudioMixer4              rmb_signalmix;         //xy=1113,565
AudioSynthWaveformDc     fireAttenDC;    //xy=1124,149
AudioEffectFade          fireFade;       //xy=1128,193
AudioEffectFade          wooshFade;      //xy=1136,310
AudioMixer4              staticMixer;    //xy=1250,846
AudioSynthWaveformModulated rmb_mod;        //xy=1278,564
AudioSynthWaveformDc     fireFilterDC;   //xy=1282,195
AudioEffectMultiply      fireAtten;      //xy=1284,154
AudioEffectFade          pureFader;      //xy=1406,637
AudioEffectFade          staticFader;    //xy=1407,706
AudioSynthWaveformModulated rmb_carrier;    //xy=1435,564
AudioFilterStateVariable fireFilter;     //xy=1494,161
AudioMixer4              hbMixer;        //xy=1593,646
AudioEffectFade          rmb_fader;          //xy=1604,566
AudioEffectFreeverb      hbReverb;       //xy=1687,756
AudioMixer4              hbReverbMixer;  //xy=1787,662
AudioMixer4              ambMixer;       //xy=1828,528
AudioPlaySdRaw           narrationPlayer; //xy=1943,826
AudioPlaySdRaw           lanternEvents;  //xy=1948,427
AudioEffectFade          hbFade;         //xy=1964,662
AudioMixer4              mainMixer;      //xy=2212,591
AudioAmplifier           volumePot;      //xy=2491,594
AudioAmplifier           ampOut;         //xy=2665,590
AudioOutputI2S           i2sOut;         //xy=2927,590
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
AudioConnection          patchCord12(fireRaw, 0, fireHumMix, 0);
AudioConnection          patchCord13(wooshRaw, 0, wooshHumMix, 0);
AudioConnection          patchCord14(hum, 0, fireHumMix, 1);
AudioConnection          patchCord15(hum, 0, wooshHumMix, 1);
AudioConnection          patchCord16(ringMod1, ringModLP);
AudioConnection          patchCord17(sineAM, 0, noiseAM, 1);
AudioConnection          patchCord18(ringMod2, 0, noiseAM, 0);
AudioConnection          patchCord19(ringModLP, 0, staticMixer, 2);
AudioConnection          patchCord20(noiseAM, 0, preDlyFilter, 0);
AudioConnection          patchCord21(fireHumMix, fireFade);
AudioConnection          patchCord22(wooshHumMix, wooshFade);
AudioConnection          patchCord23(rmb_noise, 0, rmb_signalmix, 0);
AudioConnection          patchCord24(rmb_offset, 0, rmb_signalmix, 3);
AudioConnection          patchCord25(preDlyFilter, 1, staticMixer, 0);
AudioConnection          patchCord26(rmb_signalmix, 0, rmb_mod, 0);
AudioConnection          patchCord27(fireAttenDC, 0, fireAtten, 0);
AudioConnection          patchCord28(fireFade, 0, fireAtten, 1);
AudioConnection          patchCord29(wooshFade, 0, ambMixer, 1);
AudioConnection          patchCord30(staticMixer, staticFader);
AudioConnection          patchCord31(rmb_mod, 0, rmb_carrier, 0);
AudioConnection          patchCord32(fireFilterDC, 0, fireFilter, 1);
AudioConnection          patchCord33(fireAtten, 0, fireFilter, 0);
AudioConnection          patchCord34(pureFader, 0, hbMixer, 0);
AudioConnection          patchCord35(staticFader, 0, hbMixer, 1);
AudioConnection          patchCord36(rmb_carrier, rmb_fader);
AudioConnection          patchCord37(fireFilter, 0, ambMixer, 0);
AudioConnection          patchCord38(hbMixer, 0, hbReverbMixer, 0);
AudioConnection          patchCord39(hbMixer, hbReverb);
AudioConnection          patchCord40(rmb_fader, 0, ambMixer, 3);
AudioConnection          patchCord41(hbReverb, 0, hbReverbMixer, 1);
AudioConnection          patchCord42(hbReverbMixer, hbFade);
AudioConnection          patchCord43(ambMixer, 0, mainMixer, 1);
AudioConnection          patchCord44(narrationPlayer, 0, mainMixer, 3);
AudioConnection          patchCord45(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord46(hbFade, 0, mainMixer, 2);
AudioConnection          patchCord47(mainMixer, volumePot);
AudioConnection          patchCord48(volumePot, ampOut);
AudioConnection          patchCord49(ampOut, 0, i2sOut, 0);
AudioConnection          patchCord50(ampOut, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1133,494
// GUItool: end automatically generated code



// constants
#define WIRE_ADDR           0x2D
#define SDCARD_CS_PIN       10
#define SDCARD_MOSI_PIN     7
#define SDCARD_SCK_PIN      14
#define FLASH_CS_PIN        6

// properties
String lanternID;
int lanternIndex;


#endif