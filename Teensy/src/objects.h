#ifndef T4_OBJECTS
#define T4_OBJECTS


// instruments
#include "instruments/hb_part1_samples.h"
#include "instruments/hb_part2_samples.h"
#include "instruments/hb_part3_samples.h"
#include "instruments/hb_part4_samples.h"

// GUItool: begin automatically generated code
AudioSynthWavetable      hbSynth2;       //xy=118,365
AudioSynthWavetable      hbSynth3;       //xy=119,406
AudioSynthWavetable      hbSynth4;       //xy=119,446
AudioSynthWavetable      hbSynth1;       //xy=120,323
AudioMixer4              hbWavetableMixer; //xy=332,381
AudioSynthWaveform       noiseFiltMod;   //xy=366,780
AudioSynthNoiseWhite     noiseMod;       //xy=369,734
AudioSynthWaveformSine   sineMod;        //xy=487,578
AudioFilterStateVariable noiseBP;        //xy=522,740
AudioEffectMultiply      ringMod1;       //xy=671,571
AudioSynthWaveformSine   sineAM;         //xy=672,733
AudioEffectMultiply      ringMod2;       //xy=675,686
AudioFilterBiquad        ringModLP;      //xy=857,566
AudioEffectMultiply      noiseAM;        //xy=862,706
AudioFilterStateVariable preDlyFilter;   //xy=1049,712
AudioSynthNoiseWhite     hum;         //xy=1168.7142333984375,194.7142791748047
AudioPlaySdRaw           lanternLoop;    //xy=1179.7142333984375,241.7142791748047
AudioMixer4              staticMixer;    //xy=1254,562
AudioMixer4              loopHumMix;         //xy=1339.7142333984375,227.7142791748047
AudioEffectFade          pureFader;      //xy=1433,391
AudioEffectFade          staticFader;    //xy=1434,460
AudioSynthWaveformDc     loopAttenDC;    //xy=1530.7142333984375,160.7142791748047
AudioEffectFade          lanternLoopFade; //xy=1536.7142333984375,212.7142791748047
AudioMixer4              hbMixer;        //xy=1620,400
AudioEffectMultiply      loopAtten;      //xy=1748.7142333984375,166.7142791748047
AudioSynthWaveformDc     loopFilterDC;   //xy=1753.7142333984375,204.7142791748047
AudioEffectFreeverb      hbReverb;      //xy=1778,428
AudioMixer4              hbReverbMixer;         //xy=1956.1427841186523,414.57146072387695
AudioPlaySdRaw           lanternEvents;     //xy=1960.5714645385742,269.5714530944824
AudioPlaySdRaw           narrationPlayer;     //xy=1964.5714645385742,329.5714530944824
AudioFilterStateVariable lanternLoopFilter; //xy=1965.2857055664062,188.14286422729492
AudioMixer4              mainMixer;      //xy=2216.571464538574,307.4285774230957
AudioFilterBiquad        mainEq;        //xy=2393,307
AudioAmplifier           ampOut;           //xy=2564.571533203125,307.4285888671875
AudioOutputI2S           i2sOut;         //xy=2754.571533203125,304.4285888671875
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
AudioConnection          patchCord12(ringMod1, ringModLP);
AudioConnection          patchCord13(sineAM, 0, noiseAM, 1);
AudioConnection          patchCord14(ringMod2, 0, noiseAM, 0);
AudioConnection          patchCord15(ringModLP, 0, staticMixer, 2);
AudioConnection          patchCord16(noiseAM, 0, preDlyFilter, 0);
AudioConnection          patchCord17(preDlyFilter, 1, staticMixer, 0);
AudioConnection          patchCord18(hum, 0, loopHumMix, 0);
AudioConnection          patchCord19(lanternLoop, 0, loopHumMix, 1);
AudioConnection          patchCord20(staticMixer, staticFader);
AudioConnection          patchCord21(loopHumMix, lanternLoopFade);
AudioConnection          patchCord22(pureFader, 0, hbMixer, 0);
AudioConnection          patchCord23(staticFader, 0, hbMixer, 1);
AudioConnection          patchCord24(loopAttenDC, 0, loopAtten, 0);
AudioConnection          patchCord25(lanternLoopFade, 0, loopAtten, 1);
AudioConnection          patchCord26(hbMixer, hbReverb);
AudioConnection          patchCord27(hbMixer, 0, hbReverbMixer, 0);
AudioConnection          patchCord28(loopAtten, 0, lanternLoopFilter, 0);
AudioConnection          patchCord29(loopFilterDC, 0, lanternLoopFilter, 1);
AudioConnection          patchCord30(hbReverb, 0, hbReverbMixer, 1);
AudioConnection          patchCord31(hbReverbMixer, 0, mainMixer, 2);
AudioConnection          patchCord32(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord33(narrationPlayer, 0, mainMixer, 3);
AudioConnection          patchCord34(lanternLoopFilter, 0, mainMixer, 1);
AudioConnection          patchCord35(mainMixer, mainEq);
AudioConnection          patchCord36(mainEq, ampOut);
AudioConnection          patchCord37(ampOut, 0, i2sOut, 0);
AudioConnection          patchCord38(ampOut, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=761,331
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