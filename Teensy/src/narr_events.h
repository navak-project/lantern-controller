#ifndef NARR_EVENTS
#define NARR_EVENTS

#include <OSCMessage.h>

#include "objects.h"

// clips
String narrClipList[4] = {
    "intro",
    "rituel",
    "entredeux",
    "conclu",
};


// functions
void triggerNarration(OSCMessage &msg) {
    int clip = msg.getInt(0);
    bool play = (bool)msg.getInt(1);

    if (play) {
        playAudioFile(&narrationPlayer, "narration/" + narrClipList[clip]);
    } else {
        narrationPlayer.stop();
    }
}


#endif