void audioTest(OSCMessage &msg) {
  Serial.println("asdf");
}


// #########################
//      LANTERN EVENTS
// #########################

void setLanternID(OSCMessage &msg) {
  lanternID = msg.getInt(0);
}

void igniteLantern(OSCMessage &msg) {
  playAudioFile(&lanternEvents, "ignite.wav");
}

void extinguishLantern(OSCMessage &msg) {
  playAudioFile(&lanternEvents, "extinguish.wav");
}
