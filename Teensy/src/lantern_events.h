#ifndef LANTERN_EVENTS
#define LANTERN_EVENTS

#include "objects.h"
#include "heartbeat_events.h"
#include "audio_manager.h"

AsyncDelay dly_loopEnd;
bool loopEnded = false;


// lanternID to index mapper
// this will eventually need to be changed to use the lantern type instead
std::map<String, int> idChart = {
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
  lanternLoopFilter.octaveControl(3.5);

  // lantern loop fade out
  lanternLoopFade.fadeOut(10);
}

void setLanternID(OSCMessage &msg) {
  // Serial.println("setting lanternID");

  int length = msg.getDataLength(0);
  char id[length];
  msg.getString(0, id, length);

  // Serial.print("id: ");
  // Serial.println(String(id));

  std::map<String, int>::iterator it = idChart.find(lanternID);
  if (it != idChart.end()) {
    lanternID = it->first;
    lanternIndex = it->second;
  }

  // Serial.print("lanternID: ");
  // Serial.println(lanternID);
  // Serial.print("lanternIndex: ");
  // Serial.println(lanternIndex);
}

void igniteLantern(OSCMessage &msg) {
  AudioNoInterrupts();

  // set internal properties
  setLanternID(msg);
  setHeartRate(msg.getInt(1));

  // fade in
  playAudioFile(&lanternLoop, "lantern_loops/lantern_loop_" + String(lanternIndex), true);
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
  lanternLoopFade.fadeOut(2000);

  // turn off lantern loop in 5s
  dly_loopEnd.start(5000, AsyncDelay::MILLIS);
  loopEnded = false;

  // turn off heartbeat
  fadeOutAll();
  
  AudioInterrupts();
}

void updateLanternEvents() {
  if (!loopEnded && dly_loopEnd.isExpired()) {
    lanternLoop.stop();
    loopEnded = true;
    dly_loopEnd = AsyncDelay();
  }
}


// on enter/leave tree
void attenLanternLoop() {
  loopAttenDC.amplitude(0.5, 1000);
  loopFilterDC.amplitude(-1, 200);
}
void accentLanternLoop() {
  loopAttenDC.amplitude(1, 250);
  loopFilterDC.amplitude(0, 1000);
}


#endif
