#include <ArtnetWifi.h>
#include <FastLED.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <OSCMessage.h>

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
const String local_pc_ip = "192.168.1.15";
const String local_pc_port = "8080";
String serverName = "http://" + local_pc_ip + ":" + local_pc_port + "/";
String registerUrl = serverName + "api/lanterns/register/";
String updateStatusURL = serverName + "api/lanterns/updateStatus";
//String registerRequest = "{\"hostName\":\"" + esp_hostName_String + "\", \"macAddress\":\"" + esp_macAddress + "\", \"ipAddress\":\"" + esp_ip + "\"}"; // SEE LANTERN WIFI FILE
// ----------- [FASTLED] -----------
#define DATA_PIN 19
const int NUM_LEDS = 80;
const int num_channels = NUM_LEDS * 3;
CRGB leds[NUM_LEDS];
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
// ----------- [TIMERS] ------------
unsigned long timer[2] = {millis(), millis()};
int ledIndex[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const int BUTTON_PIN = 0;
const int LED_PIN = 13; //On board LED
bool flashState = false;
float ledState = 0;
// ----------- [TEENSY COM] ---------
const String COM_OUT_HEADER = "/audio/";


void setup()
{
  // Initilize hardware:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  InitLeds();
  InitWifi();
  InitMQTT();
  InitArtnet();
  InitWire();

  digitalWrite(LED_PIN, LOW); // LED off
}

void loop()
{
  // Artnet
  ReadArtnet();
  // MQTT
  LoopMQTT();
}

// Externaly called function trhough MQTT
void restart_esp32(){
  ESP.restart();
}

// MQTT String Parsing
void doConcat(const char *a, const char *b, char *out) {
    strcpy(out, a);
    strcat(out, b);
}

//Dont mind me
