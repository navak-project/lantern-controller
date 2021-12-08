#ifndef AUDIO_MANAGER
#define AUDIO_MANAGER

#include "objects.h"


elapsedMillis blockReportTimer;


// initialize audio library
void initAudio() {
  AudioMemory(40);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.lineOutLevel(29);

  ampOut.gain(1);
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
  if (file->isPlaying() && !steal) return;
  
  // stop and replay file at path
  file->play((path + ".raw").c_str(), loop);
}

#endif
