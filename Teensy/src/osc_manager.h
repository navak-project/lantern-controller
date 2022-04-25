#ifndef OSC_MANAGER
#define OSC_MANAGER

#include "objects.h"
#include "lantern_events.h"
#include "organique_events.h"
#include "silva_events.h"


// function headers
void receiveOSC(int byteLength);
void initOSC();
void dispatcher(OSCMessage &bundleIN);


// initialize wire communication (used for OSC)
void initOSC() {
  // Wire1
  // SCL = 16    SDA = 17
  Wire1.begin(WIRE_ADDR);
  Wire1.onReceive(receiveOSC);
}

// catchall OSC receiver callback
void receiveOSC(int byteLength) {
  Serial.println("receiving OSC...");
  
  // define OSC bundle
  OSCMessage bundleIN;

  // decode incoming OSC message
  // DO NOT  TOUCH THIS !!
  while (Wire1.available()) {
    char c = Wire1.read();
    //Serial.print(c);
    bundleIN.fill(c);
    // delayMicroseconds(100);
  }
  //Serial.println();

  if (bundleIN.hasError() > 0) {
    Serial.print("err: ");
    Serial.println(bundleIN.hasError());
    Serial.println("----------------------");
  }

  // if all is well in the world of wire messaging...
  if (!bundleIN.hasError()) {
    // ...dispatch
    dispatcher(bundleIN);
  }
}


// where all callbacks are assigned
// make sure the addresses are reflected in the ESP32 code
void dispatcher(OSCMessage &bundleIN) {
  Serial.println("dispatching...");

  // lantern events
  bundleIN.dispatch("/li",    igniteLantern);           // "li" = Lantern Ignite
  bundleIN.dispatch("/t",     switchToConstantLight);   // "t"  = Transition (to constant light)
  bundleIN.dispatch("/le",    extinguishLantern);       // "le" = Lantern Extinguish

  // organique events
  bundleIN.dispatch("/on",    enterTree);               // "on" = Organique eNter
  bundleIN.dispatch("/ox",    exitTree);                // "ox" = Organique eXit
  bundleIN.dispatch("/b",     triggerHeartbeat);        // "b"  = (heart)Beat

  // silva events
  bundleIN.dispatch("/tr",    toggleRumble);            // "tr" = Toggle Rumble
  bundleIN.dispatch("/sr",    switchRumble);      // "sr" = Switch Rumble (preset)

  Serial.println("done dispatching!");
  Serial.println("----------------------");
}

#endif
