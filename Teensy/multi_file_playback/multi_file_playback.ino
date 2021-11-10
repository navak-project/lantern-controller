#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=189,220
AudioPlaySdWav           playSdWav2;     //xy=189,284
AudioPlaySdWav           playSdWav3;     //xy=191,348
AudioPlaySdWav           playSdWav4;     //xy=195,408
AudioMixer4              mixer2;         //xy=459,396
AudioMixer4              mixer1;         //xy=460,261
AudioOutputI2S           i2s;           //xy=808,373
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord3(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord4(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord5(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord6(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord7(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord8(playSdWav4, 1, mixer2, 3);
AudioConnection          patchCord9(mixer2, 0, i2s, 1);
AudioConnection          patchCord10(mixer1, 0, i2s, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=500,573
// GUItool: end automatically generated code

Bounce button0 = Bounce(0, 15);

#define SDCARD_CS_PIN   10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN  14

void setup() {
  // initialize serial + audio memory
  Serial.begin(9600);
  AudioMemory(20);

  // enable soundchip
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  sgtl5000_1.lineOutLevel(18);

  // mixer gains
  mixer1.gain(0, 1);
  mixer1.gain(1, 1);
  mixer1.gain(2, 1);
  mixer1.gain(3, 0.5);
  mixer2.gain(0, 1);
  mixer2.gain(1, 1);
  mixer2.gain(2, 1);
  mixer2.gain(3, 0.5);

  // initialize SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  // button input
  pinMode(0, INPUT_PULLUP);

  // initial delay
  delay(1000);

  // connect to ESP32 controller
  Wire1.setSCL(16);
  Wire1.setSDA(18);
  Wire1.begin(4);        // Wire1 because we are using the 2nd I2C bus
  Wire1.onReceive(receiveEvent);
}

elapsedMillis absTime;
elapsedMillis blockReport;

void receiveEvent(int howMany) {
  while (1 < Wire1.available()) {
    char c = Wire1.read();
    Serial.print(c);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if (playSdWav1.isPlaying() == false) {
    Serial.println("Start playing tone1.wav");
    playSdWav1.play("tone1.wav");
    delay(10);
  }

  if (playSdWav2.isPlaying() == false && absTime > 3000) {
    Serial.println("Start playing tone2.wav");
    playSdWav2.play("tone2.wav");
    delay(10);
  }

  if (playSdWav3.isPlaying() == false && absTime > 6000) {
    Serial.println("Start playing tone3.wav");
    playSdWav3.play("tone3.wav");
    delay(10);
  }

  button0.update();
  if (button0.fallingEdge() && playSdWav4.isPlaying() == false) {
    Serial.println("Start playing tone4.wav");
    playSdWav4.play("netflix.wav");
    delay(10);
  }
 
  // check max audio memory usage twice every second
  // the value displayed here will gauge the value we'll need to enter in the call to AudioMemory() earlier in the code
  if (blockReport > 500) {
    Serial.println(AudioMemoryUsageMax());
    blockReport = 0;
  }
}
