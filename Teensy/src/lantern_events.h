#ifndef LANTERN_EVENTS
#define LANTERN_EVENTS

#include "objects.h"
#include "heartbeat_events.h"
#include "audio_manager.h"


// lanternID to index mapper
// this will eventually need to be changed to use the lantern type instead
map<String, int> idChart = {
  { "0b85", 0 },
  { "5a8e", 1 },
  { "0a99", 2 },
};


void initLantern() {
  // initialize ID to default value
  lanternID = "0b85";
  lanternIndex = 0;

  // DCs and filters...
  loopAttenDC.amplitude(1);
  loopFilterDC.amplitude(0);
  lanternLoopFilter.frequency(14000);
  lanternLoopFilter.resonance(0.2);
  lanternLoopFilter.octaveControl(2.5);
}

void setLanternID(OSCMessage &msg) {
  // Serial.println("setting lanternID");

  int length = msg.getDataLength(0);
  char id[length];
  msg.getString(0, id, length);

  // Serial.print("id: ");
  // Serial.println(String(id));

  std::map<String, int>::iterator it = idChart.begin();
  while (it != idChart.end()) {
    Serial.print(it->first);
    Serial.print(": ");
    Serial.println(it->second);
    
    if (it->first == String(id)) {
      lanternID = it->first;
      lanternIndex = it->second;
      break;
    }

    it++;
  }

  // Serial.print("lanternID: ");
  // Serial.println(lanternID);
  Serial.print("lanternIndex: ");
  Serial.println(lanternIndex);
}

void igniteLantern(OSCMessage &msg) {
  AudioNoInterrupts();

  setLanternID(msg);
  setHeartRate(msg.getInt(1));

  // lantern loop init sequence:
  // mute, play, fade out
  mainMixer.gain(1, 0);
  playAudioFile(&lanternLoop, "lantern_loops/lantern_loop_" + String(lanternIndex), true);
  lanternLoopFade.fadeOut(10);
  // wait...
  delay(10);
  // fade back in
  mainMixer.gain(1, 0.5);
  lanternLoopFade.fadeIn(5000);

  // play ignite cue
  playAudioFile(&lanternEvents, "ignites/ignite_" + String(lanternIndex));

  // start heartbeat
  startHeartbeat();

  AudioInterrupts();
}
void extinguishLantern(OSCMessage &msg) {
  AudioNoInterrupts();

  // play momentary cue
  playAudioFile(&lanternEvents, "extinguishes/extinguish_" + String(lanternIndex));

  // fade out lantern loop
  // sound will stop looping after 5000ms
  lanternLoopFade.fadeOut(2000);

  // turn off heartbeat
  fadeOutAll();
  
  AudioInterrupts();

  delay(5000);
  lanternLoop.stop();
}


// on enter/leave tree
void attenLanternLoop() {
  loopAttenDC.amplitude(0.5, 1000);
  loopFilterDC.amplitude(-1, 200);
}
void accentLanternLoop() {
  loopAttenDC.amplitude(1, 1000);
  loopFilterDC.amplitude(0, 1000);
}


#endif
