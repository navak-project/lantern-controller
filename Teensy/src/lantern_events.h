#ifndef LANTERN_EVENTS
#define LANTERN_EVENTS

#include "objects.h"
#include "heartbeat_events.h"
#include "audio_manager.h"


int lanternID;


void initLantern() {
  // immediately fade looper to 0
  // so that it can play without us hearing it until event is triggered
  // apparently we can't fade out a signal that isn't playing... thanks Paul
  mainMixer.gain(1, 0);
  lanternLoop.play("lantern_loops/lantern_loop_0.raw", true);
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
  lanternID = msg.getInt(0);
}

void igniteLantern(OSCMessage &msg) {
  setHeartRate(msg.getInt(0));

  // play momentary cue
  playAudioFile(&lanternEvents, "ignites/ignite_" + String(lanternID) + ".wav");

  // fade in lantern loop
  mainMixer.gain(1, 0.5);
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


// on enter/leave tree
void attenLanternLoop() {
  loopAttenDC.amplitude(0.5, 1000);
  loopFilterDC.amplitude(-1, 200);
}
void accentLanternLoop() {
  loopAttenDC.amplitude(1, 1000);
  loopFilterDC.amplitude(0, 1000);
}


// called in loop()
void updateLanternLoop() {
  // TODO: optimize so that it isn't constantly called
  // TODO: remove this and replace w/ looping SdWav class that i found
  
  String path = "lantern_loops/lantern_loop_" + String(lanternID) + ".raw";
  playAudioFile(&lanternLoop, path);
}

#endif
