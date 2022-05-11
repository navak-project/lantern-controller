#ifndef HEARTBEAT_EVENTS
#define HEARTBEAT_EVENTS

// includes
#include <map>
#include "objects.h"


// heart tone chart
struct HeartTone {
  int baseTone;
  int tones[4];
};

// registry
#define NUM_HEARTTONES 4
vector<HeartTone> heartToneChart = {
  {71, { 0, 7, 16, -2 }},
  {75, { 0, 5, 10, -2 }},
  {66, { 7, 0, 12, -9 }},
  {73, { 2, 0, 7,  -4 }},
};
HeartTone currentTone;

// rate
uint32_t rate_millis;

// timer stuff
AsyncDelay dly_pulse;
bool hasPulsed = false;


// function headers
void initHeartbeat();
void setHeartRate(int rate);
void startHeartbeat();
void heartBeatToPure();
void heartBeatToStatic();
void toConstantLight();
void updateHeartbeat();
void pulse();
void depulse();
void forceSync();


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
  // BPM to millis
  rate_millis = 60000 / rate;
}



/////////////////////
////// events ///////
/////////////////////

// begin heartbeat pulse
// (called when a lantern ignites)
void startHeartbeat(int rate) {
  // set heart rate
  setHeartRate(rate);

  // begin clocker
  dly_pulse.start(rate_millis, AsyncDelay::MILLIS);

  // set current tone
  currentTone = heartToneChart.at(lanternIndex % NUM_HEARTTONES);

  // reset sine mod frequency
  sineMod.frequency(pow(2.0, ((float)(currentTone.baseTone - 69)/12.0)) * 440.0 * 0.0976);

  // fade in
  hbFade.fadeIn(10);
  staticFader.fadeIn(2000);
}


// called when lantern enters tree zone
void heartBeatToPure() {
  // play transition clip
  // TODO

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
}


// called in loop()
// 
void updateHeartbeat() {
  if (!hasIgnited) return;

  uint32_t elapsed = rate_millis - (dly_pulse.getExpiry() - millis());

  // check if timer is expired:
  if (dly_pulse.isExpired())
  {
    //Serial.println("pulse");
    pulse();
    dly_pulse.repeat();

    Serial.print("expiry: ");
    Serial.println(dly_pulse.getExpiry());
    Serial.print("duration: ");
    Serial.println(dly_pulse.getDuration());
  }
  
  // after 250ms, depulse()
  else if (elapsed > 250)
  {
    depulse();
  }

  // play 250ms note (ie. release env after that time)
}


// invoked from ESP32 to force resync
void forceSync(OSCMessage &msg) {
  pulse();
  dly_pulse.restart();
}


// utilities
// TODO: optimize
void pulse() {
  if (hasPulsed) return;
  hasPulsed = true;


  // pitch + amp
  int note = currentTone.baseTone;
  int velo = random(50, 100);

  // play each voice (attack + decay slope) depending on the heart tone chart values and current lantern ID
  hbSynth1.playNote(note + currentTone.tones[0], velo);
  hbSynth2.playNote(note + currentTone.tones[1], velo);
  hbSynth3.playNote(note + currentTone.tones[2], velo);
  hbSynth4.playNote(note + currentTone.tones[3], (int)(velo * 0.5));
}

// called some time after the heart has beaten
void depulse() {
  if (!hasPulsed) return;
  hasPulsed = false;


  // stop all notes (release slope)
  hbSynth1.stop();
  hbSynth2.stop();
  hbSynth3.stop();
  hbSynth4.stop();
}

#endif
