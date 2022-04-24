#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include <FastLED.h>


// **********************
// **** Device info *****
// **********************
// ----- [Network] -----
String esp_macAddress = "";
String esp_ip = "";
String esp_hostName_String = "";
const char * esp_hostName_char = "";
// ------ [Artnet] -------
int startUniverse = 0;
// ------- [UWB] --------
const char* mqtt_panID = "";
String mqtt_panIDString = "";
// ------- [MQTT] -------
const char* mqtt_topicParent = "/lantern/";
char mqtt_clientTopicWildCard[20];
char mqtt_clientTopic[20];
char mqtt_lanternControl[20];

// *********************************
// **** Device setup variables *****
// *********************************
// ----------- [NETWORK] -----------
const char * networkName = "Silva-WIFI";
const char * networkPswd = "silvaFTW";
// const char * networkName = "BELL034";
// const char * networkPswd = "D2AA4CA6F4F4";
// ----------- [API] ---------------
const String local_pc_ip = "192.168.1.209";
const String local_pc_port = "8081";
String serverName = "http://" + local_pc_ip + ":" + local_pc_port + "/";
String registerUrl = serverName + "api/lanterns/register/";
String OnStartUpdateStatusURL = serverName + "api/lanterns";
String LoopUpdateStatusURL = serverName + "api/lanterns/updateStatus";
//String registerRequest = "{\"hostName\":\"" + esp_hostName_String + "\", \"macAddress\":\"" + esp_macAddress + "\", \"ipAddress\":\"" + esp_ip + "\"}"; // SEE LANTERN WIFI FILE

// ----------- [FASTLED] -----------
#define DATA_PIN 19
const int NUM_LEDS = 80;
const int num_channels = NUM_LEDS * 3;
CRGB leds[NUM_LEDS];
// ----------- [TIMERS] ------------
unsigned long timer[2] = {millis(), millis()};
int ledIndex[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long lanternInfoTimer = millis();
int lanternInfoMaxTime = 5000;
bool flashState = false;
float ledState = 0;

char result[8];
char signalStrenght[8];
// ----------- [ARTNET] ------------
ArtnetWifi artnet;
const int maxUniverses = num_channels / 512 + ((num_channels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];
bool sendFrame = 1;
int previousDataLength = 0;
// ----------- [MQTT] --------------
const char* mqtt_broker = "192.168.1.212";
const int mqtt_port = 1883;
// ----------- [UDP] ---------------
//const unsigned int outPort = 9999;          // remote port (not needed for receive)
//const unsigned int localPort = 10000;        // local port to listen for UDP packets (here's where we send the packets)
//WiFiUDP Udp;
//OSCErrorCode error;
// ----------- [TEENSY COM] ---------
const String COM_OUT_HEADER = "/audio/";

// ----------- [PCB LED] ------------
#define AUX_WIFI 14
#define AUX_MQTT 12
// ----------------------------------

int sensorValue;
int wifiValue;


// Externaly called function trhough MQTT
void restart_esp32() {
  ESP.restart();
}

// MQTT String Parsing
void doConcat(const char *a, const char *b, char *out) {
  strcpy(out, a);
  strcat(out, b);
}

// void Init_PCB(){
//   pinMode(AUX_MQTT, OUTPUT);
//   pinMode(AUX_WIFI, OUTPUT);

//   digitalWrite(AUX_MQTT, LOW);
//   digitalWrite(AUX_WIFI, LOW);
// }


#endif // __GLOBAL_H__