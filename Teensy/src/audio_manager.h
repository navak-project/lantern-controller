#ifndef AUDIO_MANAGER
#define AUDIO_MANAGER

#include "objects.h"


elapsedMillis blockReportTimer;


// initialize audio library
void initAudio() {
  AudioMemory(140);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.lineOutLevel(31);
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


// play an audio file
// TODO: fix looping
void playAudioFile(AudioPlaySdWav *file, String path, bool steal = false) {
  // block file playback if it's playing and we're not stealing its voice
  if (file->isPlaying() == true && steal == false) return;

  // stop and replay file at path
  AudioNoInterrupts();
  file->stop();
  file->play(path.c_str());
  delay(10);
  AudioInterrupts();
}

void playAudioFile(AudioPlaySdRaw *file, String path, bool steal = false) {
  // stop and replay file at path
  file->play(path.c_str(), true);
}

#endif
