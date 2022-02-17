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
AudioSynthWavetable      hbSynth4;       //xy=119,454
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
AudioSynthNoiseWhite     hum;         //xy=965.5475463867188,50.29761505126953
AudioPlaySdRaw           fireRaw;    //xy=965.5475616455078,136.29761123657227
AudioFilterStateVariable preDlyFilter;   //xy=1049,712
AudioMixer4              fireHumMix;         //xy=1125.5475616455078,122.29761123657227
AudioMixer4              staticMixer;    //xy=1254,562
AudioPlaySdRaw           lightRaw;     //xy=1256.083251953125,171.5833282470703
AudioSynthWaveformDc     fireAttenDC;    //xy=1311.5475616455078,70.29761123657227
AudioEffectFade          fireFade; //xy=1317.5475616455078,122.29761123657227
AudioPlaySdRaw           wooshRaw;  //xy=1409,248
AudioMixer4              lightHumMix; //xy=1415,188
AudioEffectFade          pureFader;      //xy=1433,391
AudioEffectFade          staticFader;    //xy=1434,460
AudioEffectMultiply      fireAtten;      //xy=1524.5476303100586,73.7976131439209
AudioSynthWaveformDc     fireFilterDC;   //xy=1525.5475616455078,114.29761123657227
AudioMixer4              wooshHumMix; //xy=1587,251
AudioMixer4              hbMixer;        //xy=1620,400
AudioEffectFade          lightFade;          //xy=1742.8332290649414,182.58332633972168
AudioFilterStateVariable fireFilter; //xy=1746.1190338134766,97.7261962890625
AudioEffectFade          wooshFade; //xy=1746.7499771118164,237.99999809265137
AudioEffectFreeverb      hbReverb;      //xy=1778,428
AudioMixer4              ambMixer;         //xy=1949.3332824707031,133.5833396911621
AudioMixer4              hbReverbMixer;         //xy=1956.142822265625,417.57147216796875
AudioPlaySdRaw           lanternEvents;     //xy=1960.5714645385742,269.5714530944824
AudioPlaySdRaw           narrationPlayer;     //xy=1964.5714645385742,329.5714530944824
AudioMixer4              mainMixer;      //xy=2216.571464538574,307.4285774230957
AudioAmplifier           volumePot;           //xy=2528,306
AudioAmplifier           ampOut;           //xy=2669.571533203125,306.4285888671875
AudioOutputI2S           i2sOut;         //xy=2931.571533203125,306.4285888671875
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
AudioConnection          patchCord17(hum, 0, fireHumMix, 0);
AudioConnection          patchCord18(hum, 0, lightHumMix, 1);
AudioConnection          patchCord19(hum, 0, wooshHumMix, 1);
AudioConnection          patchCord20(fireRaw, 0, fireHumMix, 1);
AudioConnection          patchCord21(preDlyFilter, 1, staticMixer, 0);
AudioConnection          patchCord22(fireHumMix, fireFade);
AudioConnection          patchCord23(staticMixer, staticFader);
AudioConnection          patchCord24(lightRaw, 0, lightHumMix, 0);
AudioConnection          patchCord25(fireAttenDC, 0, fireAtten, 0);
AudioConnection          patchCord26(fireFade, 0, fireAtten, 1);
AudioConnection          patchCord27(wooshRaw, 0, wooshHumMix, 0);
AudioConnection          patchCord28(lightHumMix, lightFade);
AudioConnection          patchCord29(pureFader, 0, hbMixer, 0);
AudioConnection          patchCord30(staticFader, 0, hbMixer, 1);
AudioConnection          patchCord31(fireAtten, 0, fireFilter, 0);
AudioConnection          patchCord32(fireFilterDC, 0, fireFilter, 1);
AudioConnection          patchCord33(wooshHumMix, wooshFade);
AudioConnection          patchCord34(hbMixer, hbReverb);
AudioConnection          patchCord35(hbMixer, 0, hbReverbMixer, 0);
AudioConnection          patchCord36(lightFade, 0, ambMixer, 1);
AudioConnection          patchCord37(fireFilter, 0, ambMixer, 0);
AudioConnection          patchCord38(wooshFade, 0, ambMixer, 2);
AudioConnection          patchCord39(hbReverb, 0, hbReverbMixer, 1);
AudioConnection          patchCord40(ambMixer, 0, mainMixer, 1);
AudioConnection          patchCord41(hbReverbMixer, 0, mainMixer, 2);
AudioConnection          patchCord42(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord43(narrationPlayer, 0, mainMixer, 3);
AudioConnection          patchCord44(mainMixer, volumePot);
AudioConnection          patchCord45(volumePot, ampOut);
AudioConnection          patchCord46(ampOut, 0, i2sOut, 0);
AudioConnection          patchCord47(ampOut, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=999.7500152587891,276.0000047683716
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