#include <ArtnetWifi.h>
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <OSCMessage.h>


#include "global.h"
#include "ESP_artnet.h"
#include "ESP_fastled.h"
#include "ESP_mqtt.h"
#include "ESP_osc.h"
#include "ESP_wifi.h"

void setup()
{
  // Initilize hardware:
  Serial.begin(115200);

  InitLeds();
  InitWifi();
  InitMQTT();
  InitArtnet();
  InitWire();
}

void loop()
{
  // Artnet
  ReadArtnet();
  // MQTT
  LoopMQTT();

  // Lantern battery and wifi signal strength
  GetLanternStatusInfo();

//  Serial.println(sensorValue);
}

//Dont mind me
