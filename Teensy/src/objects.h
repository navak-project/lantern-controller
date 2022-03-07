#ifndef T4_OBJECTS
#define T4_OBJECTS


// instruments
#include "instruments/hb_part1_samples.h"
#include "instruments/hb_part2_samples.h"
#include "instruments/hb_part3_samples.h"
#include "instruments/hb_part4_samples.h"

// GUItool: begin automatically generated code
AudioSynthWavetable      hbSynth2;       //xy=133,558
AudioSynthWavetable      hbSynth3;       //xy=134,599
AudioSynthWavetable      hbSynth4;       //xy=134,647
AudioSynthWavetable      hbSynth1;       //xy=135,516
AudioMixer4              hbWavetableMixer; //xy=347,574
AudioSynthWaveform       noiseFiltMod;   //xy=381,973
AudioSynthNoiseWhite     noiseMod;       //xy=384,927
AudioSynthWaveformSine   sineMod;        //xy=502,771
AudioFilterStateVariable noiseBP;        //xy=537,933
AudioPlaySdRaw           fireRaw;    //xy=594.797607421875,84.54761505126953
AudioPlaySdRaw           wooshRaw;  //xy=594.75,157
AudioPlaySdRaw           lightRaw;     //xy=595.333251953125,121.08331298828125
AudioSynthNoiseWhite     hum;         //xy=599.7976684570312,335.047607421875
AudioEffectMultiply      ringMod1;       //xy=686,764
AudioSynthWaveformSine   sineAM;         //xy=687,926
AudioEffectMultiply      ringMod2;       //xy=690,879
AudioFilterBiquad        ringModLP;      //xy=872,759
AudioEffectMultiply      noiseAM;        //xy=877,899
AudioMixer4              fireHumMix;         //xy=909.547607421875,102.297607421875
AudioMixer4              lightHumMix; //xy=911,217.99998474121094
AudioMixer4              wooshHumMix; //xy=913.7499771118164,342.74999809265137
AudioFilterStateVariable preDlyFilter;   //xy=1064,905
AudioSynthWaveformDc     fireAttenDC;    //xy=1143.547607421875,58.00000762939453
AudioEffectFade          fireFade; //xy=1147.547607421875,102.297607421875
AudioEffectFade          lightFade;          //xy=1148.833251953125,211.58331298828125
AudioEffectFade          wooshFade; //xy=1154.75,346
AudioMixer4              staticMixer;    //xy=1269,755
AudioSynthWaveformDc     fireFilterDC;   //xy=1301.547607421875,104.29762268066406
AudioEffectMultiply      fireAtten;      //xy=1303.547607421875,63.00000762939453
AudioEffectFade          pureFader;      //xy=1448,584
AudioEffectFade          staticFader;    //xy=1449,653
AudioFilterStateVariable fireFilter; //xy=1513.1190185546875,70.50000762939453
AudioMixer4              hbMixer;        //xy=1635,593
AudioEffectFreeverb      hbReverb;      //xy=1729,702.5
AudioMixer4              ambMixer;         //xy=1783.333251953125,189.58334350585938
AudioMixer4              hbReverbMixer;         //xy=1829.142822265625,608.5714721679688
AudioPlaySdRaw           lanternEvents;     //xy=1975.5714645385742,462.5714530944824
AudioPlaySdRaw           narrationPlayer;     //xy=1979.5714645385742,522.5714530944824
AudioEffectFade          hbFade;          //xy=2006,608.5
AudioMixer4              mainMixer;      //xy=2231.571464538574,500.4285774230957
AudioAmplifier           volumePot;           //xy=2510,503
AudioAmplifier           ampOut;           //xy=2684.571533203125,499.4285888671875
AudioOutputI2S           i2sOut;         //xy=2946.571533203125,499.4285888671875
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
AudioConnection          patchCord14(lightRaw, 0, lightHumMix, 0);
AudioConnection          patchCord15(hum, 0, fireHumMix, 1);
AudioConnection          patchCord16(hum, 0, lightHumMix, 1);
AudioConnection          patchCord17(hum, 0, wooshHumMix, 1);
AudioConnection          patchCord18(ringMod1, ringModLP);
AudioConnection          patchCord19(sineAM, 0, noiseAM, 1);
AudioConnection          patchCord20(ringMod2, 0, noiseAM, 0);
AudioConnection          patchCord21(ringModLP, 0, staticMixer, 2);
AudioConnection          patchCord22(noiseAM, 0, preDlyFilter, 0);
AudioConnection          patchCord23(fireHumMix, fireFade);
AudioConnection          patchCord24(lightHumMix, lightFade);
AudioConnection          patchCord25(wooshHumMix, wooshFade);
AudioConnection          patchCord26(preDlyFilter, 1, staticMixer, 0);
AudioConnection          patchCord27(fireAttenDC, 0, fireAtten, 0);
AudioConnection          patchCord28(fireFade, 0, fireAtten, 1);
AudioConnection          patchCord29(lightFade, 0, ambMixer, 2);
AudioConnection          patchCord30(wooshFade, 0, ambMixer, 1);
AudioConnection          patchCord31(staticMixer, staticFader);
AudioConnection          patchCord32(fireFilterDC, 0, fireFilter, 1);
AudioConnection          patchCord33(fireAtten, 0, fireFilter, 0);
AudioConnection          patchCord34(pureFader, 0, hbMixer, 0);
AudioConnection          patchCord35(staticFader, 0, hbMixer, 1);
AudioConnection          patchCord36(fireFilter, 0, ambMixer, 0);
AudioConnection          patchCord37(hbMixer, 0, hbReverbMixer, 0);
AudioConnection          patchCord38(hbMixer, hbReverb);
AudioConnection          patchCord39(hbReverb, 0, hbReverbMixer, 1);
AudioConnection          patchCord40(ambMixer, 0, mainMixer, 1);
AudioConnection          patchCord41(hbReverbMixer, hbFade);
AudioConnection          patchCord42(lanternEvents, 0, mainMixer, 0);
AudioConnection          patchCord43(narrationPlayer, 0, mainMixer, 3);
AudioConnection          patchCord44(hbFade, 0, mainMixer, 2);
AudioConnection          patchCord45(mainMixer, volumePot);
AudioConnection          patchCord46(volumePot, ampOut);
AudioConnection          patchCord47(ampOut, 0, i2sOut, 0);
AudioConnection          patchCord48(ampOut, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1074.5,483.5
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