// #########################
//      LANTERN EVENTS
// #########################
int lanternID;

bool isLanternLooping = true;
elapsedMillis lanternLoopTimer = 10000;

void initLantern() {
  lanternID = 0;
}

void setLanternID(OSCMessage &msg) {
  lanternID = msg.getInt(0);
}

void igniteLantern(OSCMessage &msg) {
  // play momentary cue
  playAudioFile(&lanternEvents, "ignites/ignite_" + String(lanternID) + ".wav");

  // fade in lantern loop
  mainMixer.gain(1, 1);
  lanternLoopFade.fadeIn(5000);

  // start heartbeat
  startHeartbeat();
}

void extinguishLantern(OSCMessage &msg) {
  // play momentary cue
  playAudioFile(&lanternEvents, "extinguishes/extinguish_" + String(lanternID) + ".wav");

  // fade out lantern loop
  // sound will stop looping after 5000ms
  lanternLoopFade.fadeOut(2000);

  // turn off heartbeat
  fadeOutAll();
}

// called in loop()
void updateLanternLoop() {
  // TODO: optimize so that it isn't constantly called
  
  String path = "lantern_loops/lantern_loop_" + String(lanternID) + ".wav";
  playAudioFile(&lanternLoop, path);
}
