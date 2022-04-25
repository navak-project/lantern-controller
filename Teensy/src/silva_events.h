#ifndef SILVA_EVENTS
#define SILVA_EVENTS

#include <OSCMessage.h>
#include <AsyncDelay.h>
#include "objects.h"
#include "lantern_events.h"

// props
int rumbleState = 0;
int rumblePreset = 0;
// timer
AsyncDelay dly_rumble;
int rumbleTime = 70;

// presets
struct RumblePreset {
    float cf;
    float cr;
    float mf;
    float mr;
    float wamp;
    float wspeed;
    float woff;
    float rtime;
};
vector<RumblePreset> presets = {
    {   70,     2,      100,    0.3,    0.1,    2.5,    0.1,    70,     },
    {   60,     1.5,    90,     1,      0.2,    2.0,    0.2,    150,    },
    {   65,     1,      80,     1.5,    0.15,   5.0,    0.15,   125,    }
};


// function headers
void rumbleOn();
void rumbleOff();


void initRumble() {
    // carrier
    rmb_carrier.begin(0.8, 70, WAVEFORM_SINE);
    rmb_carrier.frequencyModulation(2);
    // modulator
    rmb_mod.begin(0.5, 100, WAVEFORM_SINE);
    rmb_mod.frequencyModulation(0.3);
    // noise
    rmb_noise.amplitude(1);
    // wavefolder   [0.1 ; 1.1]
    rmb_wavemod.begin(0.1, 2.5, WAVEFORM_SINE);
    rmb_wavemod.offset(0.1);    // a little bit of over-gain.. >:3
    // out filter
    biquad1.setLowpass(0, 400, 0.5);

    // mixer volume
    ambMixer.gain(3, 0.3);

    // start offset generator
    dly_rumble.start(rumbleTime, AsyncDelay::MILLIS);
}

void updateRumble() {
    if (dly_rumble.isExpired()) {
        // generate new ramp destination
        rmb_offset.amplitude(random(1, 401) / 400.0 - 0.5, rumbleTime);
        // repeat interval
        dly_rumble.repeat();
    }
}

// add callbacks here
void toggleRumble(OSCMessage &msg) {
    int state = msg.getInt(0);

    // same value filter
    if (state == rumbleState) return;
    rumbleState = state;

    // turn on or off
    if (rumbleState == 1) rumbleOn();
    else if (rumbleState == 0) rumbleOff();
}

void switchRumble(OSCMessage &msg) {
    int preset = msg.getInt(0);

    // same value filter
    if (preset == rumblePreset) return;
    rumblePreset = preset;

    // current preset
    RumblePreset p = presets.at(rumblePreset);
    // update values
    AudioNoInterrupts();
    rmb_carrier.frequency(p.cf);
    rmb_carrier.frequencyModulation(p.cr);
    rmb_mod.frequency(p.mf);
    rmb_mod.frequencyModulation(p.mr);
    rmb_wavemod.frequency(p.wspeed);
    rmb_wavemod.amplitude(p.wamp);
    rmb_wavemod.offset(p.woff);
    AudioInterrupts();
}

void rumbleOn() {
    // fader on
    rmb_fader.fadeIn(2000);
    // attenuate lantern loop so we can hear it .....
    attenLanternLoop(1000);
}
void rumbleOff() {
    // fader off
    rmb_fader.fadeOut(1000);
    // bring back lantern loop
    accentLanternLoop(500);
}


#endif