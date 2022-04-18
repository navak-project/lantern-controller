#ifndef SILVA_EVENTS
#define SILVA_EVENTS

#include <OSCMessage.h>
#include <AsyncDelay.h>

#include "objects.h"

// props
int rumbleState = 0;
AsyncDelay dly_rumble;
int rumbleTime = 70;


// function headers
void rumbleOn();
void rumbleOff();


void initRumble() {
    // carrier
    rmb_carrier.begin(0.3, 70, WAVEFORM_SINE);
    rmb_carrier.frequencyModulation(2);
    // modulator
    rmb_mod.begin(0.5, 100, WAVEFORM_SINE);
    rmb_mod.frequencyModulation(0.3);
    // noise
    rmb_noise.amplitude(1);

    // mute on start
    ambMixer.gain(3, 0);
    rmb_fader.fadeOut(30);

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

    if (state == rumbleState) return;
    rumbleState = state;

    if (rumbleState == 1) rumbleOn();
    else if (rumbleState == 0) rumbleOff();
}

void rumbleOn() {
    // initially turned off
    ambMixer.gain(3, 1);
    rmb_fader.fadeIn(4000);
}
void rumbleOff() {
    rmb_fader.fadeOut(1000);
}


#endif