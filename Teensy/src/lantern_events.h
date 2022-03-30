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
  { "cf9b", 1 },
  { "c51c", 2 },
  { "c52e", 3 },
  { "ce17", 1 },
};


void initLantern() {
  AudioNoInterrupts();

  // initialize ID to default value
  lanternID = "cf9b";
  lanternIndex = 1;

  // DCs and filters...
  fireAttenDC.amplitude(1);
  fireFilterDC.amplitude(0);
  fireFilter.frequency(14000);
  fireFilter.resonance(0.2);
  fireFilter.octaveControl(3.5);

  // ambience mixer: turn off everything...
  ambMixer.gain(0, 0);
  ambMixer.gain(1, 0);
  ambMixer.gain(2, 0);

  mainMixer.gain(1, 0.75);

  fireFade.fadeOut(10);

  AudioInterrupts();
}


void setLanternID(OSCMessage &msg) {
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
}


void igniteLantern(OSCMessage &msg) {
  AudioNoInterrupts();

  // set internal properties
  setLanternID(msg);

  // start all loops here (theyre muted)
  playAudioFile(&fireRaw, "fires/fire_" + String(lanternIndex), true);
  //playAudioFile(&wooshRaw, "wooshes/woosh_" + String(lanternIndex), true);
  //playAudioFile(&lightRaw, "lights/light_" + String(lanternIndex), true);

  // fade in first fire...
  unmuteFadeIn(&ambMixer, 0, &fireFade, 5000);

  // play ignite cue
  playAudioFile(&lanternEvents, "ignites/ignite_" + String(lanternIndex));

  // start heartbeat
  startHeartbeat(msg.getInt(1));

  AudioInterrupts();
}


void switchToConstantLight(OSCMessage &msg) {
  AudioNoInterrupts();
  
  // crossfade to woosh
  fireFade.fadeOut(3000);
  unmuteFadeIn(&ambMixer, 1, &wooshFade, 6000);

  // delay (10s)
  // TODO: make a better system for this... some kinda delay queue
  dly_wooshEnd.start(10000, AsyncDelay::MILLIS);
  wooshEnded = false;

  // fade out heartbeat
  fadeOutHeartbeat();

  AudioInterrupts();
}

void extinguishLantern(OSCMessage &msg) {
  AudioNoInterrupts();

  // play momentary cue
  playAudioFile(&lanternEvents, "extinguishes/extinguish_" + String(lanternIndex));

  // fade out lantern loop
  fireFade.fadeOut(2000);
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
    // crossfade to light
    wooshFade.fadeOut(12000);
    unmuteFadeIn(&ambMixer, 2, &lightFade, 12000);

    // turn off delay
    wooshEnded = true;
    dly_wooshEnd = AsyncDelay();
  }

  // check if delay has expired
  if (!loopEnded && dly_loopEnd.isExpired()) {
    // if so, stop the lantern loop clip
    // (it is assumed that the lantern loop gain is at 0 when this happens)
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
