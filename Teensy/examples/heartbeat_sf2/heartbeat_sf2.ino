#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable1;     //xy=502,318
AudioOutputI2S           i2s;           //xy=707,317
AudioConnection          patchCord1(wavetable1, 0, i2s, 0);
AudioConnection          patchCord2(wavetable1, 0, i2s, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=500,573
// GUItool: end automatically generated code

#include "flute_01_samples.h"


void setup() {
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  
  // put your setup code here, to run once:
  wavetable1.setInstrument(flute_01);
}

elapsedMillis elapsed;

void loop() {
  // put your main code here, to run repeatedly:
  wavetable1.playFrequency(440, 0.5);
  delay(500);
  wavetable1.stop();
  delay(500);
}
