#ifndef AUDIO_MANAGER
#define AUDIO_MANAGER

#include "objects.h"

int volumePotValue = 0;
int updateFilter[5];

elapsedMillis blockReportTimer;


// initialize audio library
void initAudio() {
  AudioMemory(80);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.audioPostProcessorEnable();
  sgtl5000_1.lineOutLevel(29);
  
  // equalization
  sgtl5000_1.eqSelect(PARAMETRIC_EQUALIZER);
  // -- 1. midbass attenuation
  calcBiquad(FILTER_PARAEQ, 500, -6, 0.3, 524288, 44100, updateFilter);
  sgtl5000_1.eqFilter(0, updateFilter);
  // -- 2. high shelf gain
  // calcBiquad(FILTER_HISHELF, 4000, 6, 0.5, 524288, 44100, updateFilter);
  // sgtl5000_1.eqFilter(1, updateFilter);
  
  // global amp
  ampOut.gain(0.5);
  // hum (fixes lantern loop fade out bug when not playing...?)
  hum.amplitude(0.0001);
}


// initialize SD card
void initSD() {
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}


// monitor audio memory usage
void monitorBlocks() {
  if (blockReportTimer > 500) {
    Serial.println(AudioMemoryUsageMax());
    blockReportTimer = 0;
  }
}


// play an audio file (no need to specify the extension every time)
void playAudioFile(AudioPlaySdRaw *file, String path, bool loop = false, bool steal = false) {
  // if steal is set to false, the clip will not restart if it already is playing
  if (file->isPlaying() && !steal) return;

  // stop and replay file at path
  file->play((path + ".raw").c_str(), loop);
}


// update global amp with value from A1 pin
void updateVolumePot() {
  int val = analogRead(A1);
  if (val != volumePotValue) {
    volumePot.gain((float)val / 1024.0);
    volumePotValue = val;
  }
}

#endif
