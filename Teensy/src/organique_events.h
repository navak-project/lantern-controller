#ifndef ORGANIQUE_EVENTS
#define ORGANIQUE_EVENTS

#include "lantern_events.h"
#include "heartbeat_events.h"


// OSC callback -- when lantern enters tree zone
void enterTree(OSCMessage &msg) {
    attenLanternLoop();     // in lantern_events
    heartBeatToPure();      // in heartbeat_events
}

// OSC callback -- when lantern leaves tree zone
void exitTree(OSCMessage &msg) {
    accentLanternLoop();    // in lantern_events
    heartBeatToStatic();    // in heartbeat_events
}

#endif