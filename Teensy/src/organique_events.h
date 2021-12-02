#ifndef ORGANIQUE_EVENTS
#define ORGANIQUE_EVENTS

#include "lantern_events.h"
#include "heartbeat_events.h"

void enterTree(OSCMessage &msg) {
    attenLanternLoop();
    heartBeatToPure();
}

void leaveTree(OSCMessage &msg) {
    accentLanternLoop();
    heartBeatToStatic();
}

#endif