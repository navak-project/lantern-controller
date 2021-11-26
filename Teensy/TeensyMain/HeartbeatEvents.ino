int heartRateBPM;
unsigned long heartRateMillis;

bool heartbeatStarted = false;
elapsedMillis heartbeatTimer;

// NICE TO HAVE: occasional (40% chance) intermediate random-offset pulse

void initHeartbeat() {
  setHeartRate(70);
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
}

void updateHeartbeat() {
  if (!heartbeatStarted) return;
  
  if (heartbeatTimer > heartRateMillis) {
    heartbeatTimer = 0;

    // trigger instrument
  }

  // add check for stopping wavetable
}
