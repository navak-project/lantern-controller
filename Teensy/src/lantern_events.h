#ifndef LANTERN_EVENTS
#define LANTERN_EVENTS

#include "objects.h"
#include "heartbeat_events.h"
#include "audio_manager.h"

AsyncDelay dly_loopEnd;
AsyncDelay dly_wooshEnd;

bool loopEnded = false;
bool wooshEnded = false;


// lanternID to index mapper
// this will eventually need to be changed to use the lantern type instead
std::map<String, int> idChart = {
  { "0b85", 1 },
  { "5a8e", 2 },
  { "0a99", 3 },
};


void initLantern() {
  // initialize ID to default value
  lanternID = "0b85";
  lanternIndex = 0;

  // DCs and filters...
  fireAttenDC.amplitude(1);
  fireFilterDC.amplitude(0);
  fireFilter.frequency(14000);
  fireFilter.resonance(0.2);
  fireFilter.octaveControl(3.5);

  // mixer shit
  ambMixer.gain(0, 1);

  // lantern loop fade out
  fireFade.fadeOut(10);
  lightFade.fadeOut(10);
  wooshFade.fadeOut(10);
}

void setLanternID(OSCMessage &msg) {
  // Serial.println("setting lanternID");

  // decode OSC message
  int length = msg.getDataLength(0);
  char id[length];
  msg.getString(0, id, length);
  // set lantern ID
  lanternID = id;

  // find index
  // will be removed eventually
  std::map<String, int>::iterator it = idChart.find(lanternID);
  if (it != idChart.end()) {
    lanternID = it->first;
    lanternIndex = it->second;
  }

  Serial.println(lanternIndex);

  // Serial.print("lanternID: ");
  // Serial.println(lanternID);
  // Serial.print("lanternIndex: ");
  // Serial.println(lanternIndex);
}

void igniteLantern(OSCMessage &msg) {
  AudioNoInterrupts();

  // set internal properties
  setLanternID(msg);

  // start lantern loop layer 1
  playAudioFile(&fireRaw, "fires/fire_" + String(lanternIndex), true);
  fireFade.fadeIn(5000);

  // play ignite cue
  playAudioFile(&lanternEvents, "ignites/ignite_" + String(lanternIndex));

  // start heartbeat
  startHeartbeat(msg.getInt(1));

  AudioInterrupts();
}

void switchToConstantLight(OSCMessage &msg) {
  // start woosh sound
  playAudioFile(&wooshRaw, "wooshes/woosh_" + String(lanternIndex), true);
  
  // crossfade to woosh
  fireFade.fadeOut(3000);
  wooshFade.fadeIn(6000);

  // delay (10s)
  dly_wooshEnd.start(10000, AsyncDelay::MILLIS);
  wooshEnded = false;
}

void extinguishLantern(OSCMessage &msg) {
  AudioNoInterrupts();

  // play momentary cue
  playAudioFile(&lanternEvents, "extinguishes/extinguish_" + String(lanternIndex));

  // fade out lantern loop
  lightFade.fadeOut(2000);

  // turn off lantern loop in 5s
  dly_loopEnd.start(5000, AsyncDelay::MILLIS);
  loopEnded = false;

  // turn off heartbeat
  fadeOutAll();
  
  AudioInterrupts();
}

void updateLanternEvents() {
  // woosh fade in end delay
  if (!wooshEnded && dly_wooshEnd.isExpired()) {
    fireRaw.stop();

    // start light clip
    playAudioFile(&lightRaw, "lights/light_" + String(lanternIndex), true);
    
    // crossfade to light
    wooshFade.fadeOut(12000);
    lightFade.fadeIn(12000);

    // turn off delay
    wooshEnded = true;
    dly_wooshEnd = AsyncDelay();
  }

  // check if delay has expired
  if (!loopEnded && dly_loopEnd.isExpired()) {
    // if so, stop the lantern loop clip
    // (it is assumed that the lantern loop gain is at 0 when this happens)
    wooshRaw.stop();
    lightRaw.stop();

    loopEnded = true;
    dly_loopEnd = AsyncDelay();
  }
}


// when entering a tree zone
void attenLanternLoop() {
  fireAttenDC.amplitude(0.5, 1000);
  fireFilterDC.amplitude(-1, 200);
}

// when leaving a tree zone
void accentLanternLoop() {
  fireAttenDC.amplitude(1, 250);
  fireFilterDC.amplitude(0, 1000);
}


#endif
