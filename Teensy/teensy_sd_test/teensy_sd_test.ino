#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav;     //xy=234,236
AudioOutputI2S           i2s1;           //xy=566,238
AudioConnection          patchCord1(playSdWav, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000;     //xy=352,464
// GUItool: end automatically generated code

Bounce button0 = Bounce(0, 15);   // 15 = 15 ms debounce time

#define SDCARD_CS_PIN   10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN  14

void setup() {
  Serial.begin(115200);
  AudioMemory(8);

  // initialize audio chip
  sgtl5000.enable();
  sgtl5000.volume(0.5);

  // initialize SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  // initialize buttons
  pinMode(0, INPUT_PULLUP);
  delay(1000);
}

void loop() {
  Serial.println(playSdWav.isPlaying());
  
  // play sound once if it isn't playing already when pressing button
  button0.update();
  if (button0.fallingEdge() && playSdWav.isPlaying() == false) {
    Serial.print("Start playing netflix.wav");
    playSdWav.play("pad.wav");
    delay(10);  // wait for library to parse WAV info
  }
}
