int heartRateBPM;
unsigned long heartRateMillis;

bool heartbeatStarted = false;
bool isHeartNotePlaying = false;
elapsedMillis heartbeatTimer;

// NICE TO HAVE: occasional (40% chance) intermediate random-offset pulse

void initHeartbeat() {
  // set initial heart rate
  // TODO: remove this and manage from ESP32 messaging instead
  setHeartRate(70);


  // configure WT instruments
  hbSynth1.setInstrument(hb_part1);
  hbSynth1.amplitude(1);
  hbSynth2.setInstrument(hb_part2);
  hbSynth2.amplitude(1);
  hbSynth3.setInstrument(hb_part3);
  hbSynth3.amplitude(1);
  hbSynth4.setInstrument(hb_part4);
  hbSynth4.amplitude(1);


  // configure WT mixer
  hbWavetableMixer.gain(0, 1);
  hbWavetableMixer.gain(1, 1);
  hbWavetableMixer.gain(2, 1);
  hbWavetableMixer.gain(3, 1);


  // configure LFO parameters
  sineMod1.frequency(0.08);
  sineMod1.amplitude(0.5);
  sineMod1.offset(0.5);

  sineMod2.frequency(0.13);
  sineMod2.amplitude(0.5);
  sineMod2.offset(0.5);

  sineMod3.frequency(0.11);
  sineMod3.amplitude(0.5);
  sineMod3.offset(0.5);


  // configure RM network
  sineRing1.frequency(5600);
  sineRing1.amplitude(1);
  sineRing1.frequencyModulation(0.07);    // [5600 - 6000]

  sineRing2.frequency(2000);
  sineRing2.amplitude(1);
  sineRing2.frequencyModulation(0.1);     // [2000 - 2200]

  sineRing3.frequency(140);
  sineRing3.amplitude(1);
  sineRing3.frequencyModulation(0.15);    // [140 - 161]


  // configure static mixer gains
  hbStaticMixer.gain(0, 0.125);
  hbStaticMixer.gain(1, 0.25);
  hbStaticMixer.gain(2, 0.5);
  hbStaticMixer.gain(3, 0.125);


  // configure static filter
  staticFilter.setLowpass(0, 4000, 0.3);


  // mix pure and static signals
  // TODO: react to tree area enter/leave events
  hbMixer.gain(0, 1);
  hbMixer.gain(1, 1);
  mainMixer.gain(2, 1);


  // initialize faders
  hbPureFader.fadeOut(10);
  hbStaticFader.fadeOut(10);
}

void setHeartRate(int rate) {
  heartRateBPM = rate;
  heartRateMillis = 60000 / rate;
}



/////////////////////
////// events ///////
/////////////////////

void startHeartbeat() {
  // begin heartbeat loop
  heartbeatTimer = 0;
  heartbeatStarted = true;

  hbStaticFader.fadeIn(2000);
}

void attenuateHeartbeat() {
  // lower filter for heartbeat
}

void toConstantLight() {
  // fade out heartbeat,
  // fade in constant light
}

void fadeOutAll() {
  // turn off all vital energy instruments
  heartbeatStarted = false;
  stopHeartNote();
}

void updateHeartbeat() {
  if (!heartbeatStarted) return;
  
  if (heartbeatTimer > heartRateMillis) {
    heartbeatTimer = 0;

    // trigger instrument
    // NOTE TO SELF FOR THE FUTURE:
    // THIS IS MIDI VELOCITY!!!! NOT SIGNAL AMPLITUDE!!! LOLLL
    int velo = random(30, 100);
    playHeartNote(72, velo);
  }

  // play 250ms note (ie. release env after that time)
  if (heartbeatTimer > 250 && isHeartNotePlaying) {
    stopHeartNote();
  }
}


// utilities
// TODO: optimize
void playHeartNote(int note, int velo) {
  hbSynth1.playNote(note, velo);
  hbSynth2.playNote(note + 7, velo);
  hbSynth3.playNote(note + 14, velo);
  hbSynth4.playNote(note, velo);

  isHeartNotePlaying = true;
}

void stopHeartNote() {
  hbSynth1.stop();
  hbSynth2.stop();
  hbSynth3.stop();
  hbSynth4.stop();

  isHeartNotePlaying = false;
}
