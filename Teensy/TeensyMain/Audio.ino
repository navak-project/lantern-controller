elapsedMillis blockReportTimer;


// initialize audio library
void initAudio() {
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  AudioMemory(20);
}


// monitor audio memory usage
void monitorBlocks() {
  if (blockReportTimer > 500) {
    Serial.println(AudioMemoryUsageMax());
    blockReportTimer = 0;
  }
}


// play an audio file
void playAudioFile(AudioPlaySdWav *file, const char* path) {
  if (file->isPlaying() == false) {
    file->play(path);
    delay(10);
  }
}
