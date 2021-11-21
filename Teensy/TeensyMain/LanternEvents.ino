// #########################
//      LANTERN EVENTS
// #########################
bool isLanternLooping = false;
elapsedMillis lanternLoopTimer = 10000;

void setLanternID(OSCMessage &msg) {
  lanternID = msg.getInt(0);
}

void igniteLantern(OSCMessage &msg) {
  // play momentary cue
  playAudioFile(&lanternEvents, "ignite.wav");

  // start lantern loop
  isLanternLooping = true;

  // fade in lantern loop
  lanternLoopFade.fadeIn(5000);
}

void extinguishLantern(OSCMessage &msg) {
  // play momentary cue
  playAudioFile(&lanternEvents, "extinguish.wav");

  // reset timer
  lanternLoopTimer = 0;

  // fade out lantern loop
  // sound will stop looping after 5000ms
  lanternLoopFade.fadeOut(5000);
}

// called in loop()
void updateLanternLoop() {
  if (!isLanternLooping && lanternLoopTimer > 5000) return;

  String path = "lantern_loop_" + String(lanternID) + ".wav";
  playAudioFile(&lanternLoop, path);
}
