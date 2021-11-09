#include <ArtnetWifi.h>
#include <FastLED.h>
#include <WiFi.h>
//#include <ArduinoJson.h>

//FastLED Stuff
// DataPin out for LED
#define DATA_PIN 19

//FastLED stuff
// Define the array of leds
const int NUM_LEDS = 65;
const int num_channels = NUM_LEDS * 3;
CRGB leds[NUM_LEDS];

// Timer vars
unsigned long timer[2] = {millis(), millis()};
// LED Indexs
int ledIndex[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Wifi stuff
// WiFi network name and password:
const char * networkName = "Silva-WIFI";
const char * networkPswd = "silvaFTW";
//// WORK FROM HOME
//const char * networkName = "BELL034";
//const char * networkPswd = "D2AA4CA6F4F4";

//// Internet domain to request from:
//const char * hostDomain = "example.com";
//const int hostPort = 80;

//Artnet stuff
//Artnet settings
ArtnetWifi artnet;
int startUniverse = 1;
// Check if we got all universes
const int maxUniverses = num_channels / 512 + ((num_channels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];
bool sendFrame = 1;
int previousDataLength = 0;

const int BUTTON_PIN = 0;
const int LED_PIN = 13; //On board LED

//Sequence vars
bool flashState = false;

//OSC
// A UDP instance to let us send and receive packets over UDP
//WiFiUDP Udp;
//const IPAddress outIp(10,40,10,105);        // remote IP (not needed for receive)
const unsigned int outPort = 9999;          // remote port (not needed for receive)
const unsigned int localPort = 10000;        // local port to listen for UDP packets (here's where we send the packets)

//OSCErrorCode error;
float ledState = 0;


void setup()
{
  // Initilize hardware:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  InitLeds();
  InitWifi();
  InitArtnet();

  digitalWrite(LED_PIN, LOW); // LED off
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == LOW)
  { // Check if button has been pressed
    while (digitalRead(BUTTON_PIN) == LOW); // Wait for button to be released

    digitalWrite(LED_PIN, HIGH); // Turn on LED
//    requestURL(hostDomain, hostPort); // Connect to server
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }

  // Artnet
  ReadArtnet();
}


//Dont mind me
