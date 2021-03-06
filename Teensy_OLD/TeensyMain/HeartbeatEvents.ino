int heartRateBPM;
unsigned long heartRateMillis;
int heartNote = 74;

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
  

  // STATIC CONFIGURATION V2!!

  // first ring mod (sine wave, low frequency for good rumble)
  sineMod.frequency(pow(2.0, ((float)(heartNote - 69)/12.0)) * 440.0 * 0.0976);
  ringModLP.setLowpass(0, 1500, 0.3);

  // noisy ring mod w/ slight AM and filter modulation
  noiseMod.amplitude(0.25);
  noiseFiltMod.begin(WAVEFORM_SINE);
  noiseFiltMod.frequency(0.07);
  noiseFiltMod.amplitude(0.5);
  noiseFiltMod.offset(0.5);
  noiseBP.frequency(1500);
  noiseBP.resonance(0.3);
  noiseBP.octaveControl(1);
  sineAM.amplitude(1);
  sineAM.frequency(4);

  // simple echo
  preDlyFilter.frequency(4000);
  preDlyFilter.resonance(0.3);
  noiseDly.delay(0, 300);
  preDlyMixer.gain(1, 0.5);   // feedback level
  staticMixer.gain(1, 0.25);


  // mix pure and static signals
  // TODO: react to tree area enter/leave events
  hbMixer.gain(0, 1);
  hbMixer.gain(1, 2);

  // initialize faders
  pureFader.fadeOut(10);
  staticFader.fadeOut(10);

  // to main mixer
  mainMixer.gain(2, 1);
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

  staticFader.fadeIn(2000);
}


// enter/leave tree events
void heartBeatToPure() {
  staticFader.fadeOut(500);
  pureFader.fadeIn(500);
}
void heartBeatToStatic() {
  staticFader.fadeIn(500);
  pureFader.fadeOut(500);
} 


// towards Silva ....
void toConstantLight() {
  // fade out heartbeat,
  // fade in constant light
}


// ending
void fadeOutAll() {
  // turn off all vital energy instruments
  heartbeatStarted = false;
  releaseHeartNote();
}


// called in loop()
void updateHeartbeat() {
  if (!heartbeatStarted) return;
  
  if (heartbeatTimer > heartRateMillis) {
    heartbeatTimer = 0;

    // trigger instrument
    // NOTE TO SELF FOR THE FUTURE:
    // THIS IS MIDI VELOCITY!!!! NOT SIGNAL AMPLITUDE!!! LOLLL
    int velo = random(50, 100);
    actionsOnPulse();
    pulseHeartNote(heartNote, velo);
  }

  // play 250ms note (ie. release env after that time)
  if (heartbeatTimer > 250 && isHeartNotePlaying) {
    releaseHeartNote();
  }
}


// utilities
// TODO: optimize
void pulseHeartNote(int note, int velo) {
  // TODO: velocity + note modulation
  // so that each note does not play at the same velocity on its own

  hbSynth1.playNote(note, velo);
  hbSynth2.playNote(note + 7, velo);
  hbSynth3.playNote(note + 14, velo);
  hbSynth4.playNote(note, (int)(velo * 0.5));

  isHeartNotePlaying = true;
}

void actionsOnPulse() {
  // sine mod frequency
}

void releaseHeartNote() {
  hbSynth1.stop();
  hbSynth2.stop();
  hbSynth3.stop();
  hbSynth4.stop();

  // play pulse drawback?

  isHeartNotePlaying = false;
}
