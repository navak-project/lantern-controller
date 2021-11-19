void audioTest(OSCMessage &msg) {
  Serial.println("asdf");
}


// #########################
//      LANTERN EVENTS
// #########################

void igniteLantern(OSCMessage &msg) {
  playAudioFile(&lanternEvents, "ignite.wav");
}

void extinguishLantern(OSCMessage &msg) {
  playAudioFile(&lanternEvents, "extinguish.wav");
}
