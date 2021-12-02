void enterTree(OSCMessage &msg) {
    attenLanternLoop();
    heartBeatToPure();
}

void leaveTree(OSCMessage &msg) {
    accentLanternLoop();
    heartBeatToStatic();
}