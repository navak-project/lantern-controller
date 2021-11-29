int heartRateBPM;
unsigned long heartRateMillis;

bool heartbeatStarted = false;
elapsedMillis heartbeatTimer;

// NICE TO HAVE: occasional (40% chance) intermediate random-offset pulse

void initHeartbeat() {
  setHeartRate(100);

  // initialize instruments
  hbSynth1.setInstrument(flute_01);
  hbSynth1.amplitude(1);
  
  hbMixer.gain(0, 1);
  mainMixer.gain(2, 0.5);
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
  hbSynth1.stop();
}

void updateHeartbeat() {
  if (!heartbeatStarted) return;
  
  if (heartbeatTimer > heartRateMillis) {
    heartbeatTimer = 0;

    // trigger instrument
    hbSynth1.playFrequency(660);
  }

//  // add check for stopping wavetable
  if (heartbeatTimer > heartRateMillis - 200 && hbSynth1.isPlaying()) {
    hbSynth1.stop();
  }
}
