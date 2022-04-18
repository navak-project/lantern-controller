#ifndef HEARTBEAT_EVENTS
#define HEARTBEAT_EVENTS


// includes
#include <map>

#include "objects.h"

// timers
AsyncDelay dly_hbEnd;
bool hbEnded = false;


// heart tone chart
struct HeartTone {
  int baseTone;
  int tones[4];
};

std::map<String, HeartTone> heartToneChart = {
  { "cf9b", {71, { 0, 7, 16, -2 }} },
  { "c51c", {75, { 0, 5, 10, -2 }} },
  { "c52e", {66, { 7, 0, 12, -9 }} },
  { "ce17", {73, { 2, 0, 7,  -4 }} },
};


// props
int heartRateBPM;                 // heart rate in beats per second
unsigned long heartRateMillis;    // heart rate as a millisecond interval between each beat

elapsedMillis heartbeatTimer;     // interval timer
bool heartbeatStarted = false;
bool isHeartNotePlaying = false;
bool cuePulse = false;


// function headers
void initHeartbeat();
void setHeartRate(int rate);
void startHeartbeat();
void heartBeatToPure();
void heartBeatToStatic();
void toConstantLight();
void fadeOutAll();
void updateHeartbeat();
void pulseHeartNote(int note, int velo);
void actionsOnPulse();
void releaseHeartNote();


// initialize heartbeat properties/DSP
void initHeartbeat() {
  // set initial heart rate
  // TODO: remove this and manage from ESP32 messaging instead
  setHeartRate(70);

  // reverb
  hbReverb.roomsize(0.4);
  hbReverb.damping(0.1);
  hbReverbMixer.gain(1, 0.5);


  // configure WT instruments
  hbSynth1.setInstrument(hb_part1);
  hbSynth1.amplitude(1);
  hbSynth2.setInstrument(hb_part2);
  hbSynth2.amplitude(1);
  hbSynth3.setInstrument(hb_part3);
  hbSynth3.amplitude(1);
  hbSynth4.setInstrument(hb_part4);
  hbSynth4.amplitude(1);


  // configure WT mixer
  hbWavetableMixer.gain(0, 1);
  hbWavetableMixer.gain(1, 1);
  hbWavetableMixer.gain(2, 1);
  hbWavetableMixer.gain(3, 1);
  

  // STATIC CONFIGURATION V2!!

  // first ring mod (sine wave, low frequency for good rumble)
  ringModLP.setLowpass(0, 1500, 0.3);

  // noisy ring mod w/ slight AM and filter modulation
  noiseMod.amplitude(0.25);
  noiseFiltMod.begin(WAVEFORM_SINE);
  noiseFiltMod.frequency(0.07);
  noiseFiltMod.amplitude(0.5);
  noiseFiltMod.offset(0.5);
  noiseBP.frequency(1500);
  noiseBP.resonance(0.3);
  noiseBP.octaveControl(1);
  sineAM.amplitude(1);
  sineAM.frequency(4);

  // simple echo
  preDlyFilter.frequency(4000);
  preDlyFilter.resonance(0.3);
  staticMixer.gain(1, 0.25);


  // mix pure and static signals
  hbMixer.gain(0, 1);
  hbMixer.gain(1, 2);

  // to main mixer
  mainMixer.gain(2, 1.2);
}


// convert heart rate to ms interval
void setHeartRate(int rate) {
  heartRateBPM = rate;
  heartRateMillis = 60000 / rate;
}



/////////////////////
////// events ///////
/////////////////////

// begin heartbeat pulse
// (called when a lantern ignites)
void startHeartbeat(int rate) {
  setHeartRate(rate);

  // begin heartbeat loop
  heartbeatTimer = 0;
  // heartbeatStarted = true;

  // reset sine mod frequency
  sineMod.frequency(pow(2.0, ((float)(heartToneChart[lanternID].baseTone - 69)/12.0)) * 440.0 * 0.0976);

  // fade in
  staticFader.fadeIn(2000);
}


void pulse() {
  cuePulse = true;
}


// called when lantern enters tree zone
void heartBeatToPure() {
  // play transition clip

  // crossfade
  staticFader.fadeOut(250);
  pureFader.fadeIn(250);
}

// called when lantern leaves tree zone
void heartBeatToStatic() {
  // play transition clip

  // crossfade
  staticFader.fadeIn(250);
  pureFader.fadeOut(250);
}


// towards Silva ....
void fadeOutHeartbeat() {
  // fade out heartbeat
  hbFade.fadeOut(10000);

  // start heart beat stop timer
  hbEnded = false;
  dly_hbEnd.start(10000, AsyncDelay::MILLIS);
}


// stop heartbeat (DEPRECATED)
void fadeOutAll() {
  // turn off all vital energy instruments
  heartbeatStarted = false;
  //releaseHeartNote();
}


// called in loop()
// 
void updateHeartbeat() {
  if (!cuePulse) return;

  // // check for heart beat delay end
  // if (!hbEnded && dly_hbEnd.isExpired()) {
  //   heartbeatStarted = false;

  //   // kill timer
  //   hbEnded = true;
  //   dly_hbEnd = AsyncDelay();
  // }
  
  // after heart rate interval (derived from BPM value)
  if (heartbeatTimer > heartRateMillis) {
    // reset timer
    heartbeatTimer = 0;

    // trigger instrument
    // NOTE TO SELF FOR THE FUTURE:
    // THIS IS MIDI VELOCITY!!!! NOT SIGNAL AMPLITUDE!!! LOLLL
    int velo = random(50, 100);
    actionsOnPulse();
    pulseHeartNote(heartToneChart[lanternID].baseTone, velo);
  }

  // play 250ms note (ie. release env after that time)
  if (heartbeatTimer > 250 && isHeartNotePlaying) {
    releaseHeartNote();
  }
}


// utilities
// TODO: optimize
void pulseHeartNote(int note, int velo) {
  // TODO: velocity + note modulation
  // so that each note does not play at the same velocity on its own

  // play each voice (attack + decay slope) depending on the heart tone chart values and current lantern ID
  hbSynth1.playNote(note + heartToneChart[lanternID].tones[0], velo);
  hbSynth2.playNote(note + heartToneChart[lanternID].tones[1], velo);
  hbSynth3.playNote(note + heartToneChart[lanternID].tones[2], velo);
  hbSynth4.playNote(note + heartToneChart[lanternID].tones[3], (int)(velo * 0.5));

  // toggle flag
  isHeartNotePlaying = true;
}

// called on each pulse
void actionsOnPulse() {
  // sine mod frequency
}

// called some time after the heart has beaten
void releaseHeartNote() {
  // stop all notes (release slope)
  hbSynth1.stop();
  hbSynth2.stop();
  hbSynth3.stop();
  hbSynth4.stop();

  // toggle flags
  isHeartNotePlaying = false;
  cuePulse = false;
}

#endif
