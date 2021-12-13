#ifndef LANTERN_EVENTS
#define LANTERN_EVENTS

#include "objects.h"
#include "heartbeat_events.h"
#include "audio_manager.h"
#include <map>


int lanternID;
// lanternID to index mapper
// this will eventually need to be changed to use the lantern type instead
std::map<String, int> idChart = {
  { "0b85", 0 },
  { "5a8e", 1 },
  { "0a99", 2 },
};


void initLantern() {
  // immediately fade looper to 0
  // so that it can play without us hearing it until event is triggered
  // apparently we can't fade out a signal that isn't playing... thanks Paul
  mainMixer.gain(1, 0);
  playAudioFile(&lanternLoop, "lantern_loops/lantern_loop_" + String(lanternID), true);
  lanternLoopFade.fadeOut(10);

  // initialize ID
  lanternID = 0;

  // DCs and filters...
  loopAttenDC.amplitude(1);
  loopFilterDC.amplitude(0);

  lanternLoopFilter.frequency(16000);
  lanternLoopFilter.resonance(0.2);
  lanternLoopFilter.octaveControl(2.5);
}

void setLanternID(OSCMessage &msg) {
  Serial.println("setting lanternID");

  int length = msg.getDataLength(0);
  char id[length];
  msg.getString(0, id, length);

  Serial.print("id: ");
  Serial.println(String(id));

  std::map<String, int>::iterator it = idChart.begin();
  while (it != idChart.end()) {
    Serial.print(it->first);
    Serial.print(": ");
    Serial.println(it->second);
    
    if (it->first == String(id)) {
      lanternID = it->second;
      break;
    }

    it++;
  }

  Serial.print("lanternID: ");
  Serial.println(lanternID);
}

void igniteLantern(OSCMessage &msg) {
  setLanternID(msg);
  setHeartRate(msg.getInt(1));

  // // play momentary cue
  playAudioFile(&lanternEvents, "ignites/ignite_" + String(lanternID));

  // // fade in lantern loop
  mainMixer.gain(1, 0.5);
  lanternLoopFade.fadeIn(5000);

  // // start heartbeat
  startHeartbeat();
}
void extinguishLantern(OSCMessage &msg) {
  AudioNoInterrupts();
  // play momentary cue
  playAudioFile(&lanternEvents, "extinguishes/extinguish_" + String(lanternID));

  // fade out lantern loop
  // sound will stop looping after 5000ms
  lanternLoopFade.fadeOut(2000);

  // turn off heartbeat
  fadeOutAll();
  AudioInterrupts();
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
