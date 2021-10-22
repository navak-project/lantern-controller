#include <WiFi.h>
#include <FastLED.h>
#include <WifiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>


#define NUM_LEDS 104
#define DATA_PIN 19

// WiFi network name and password:
const char * networkName = "Silva-WIFI";
const char * networkPswd = "silvaFTW";

// Internet domain to request from:
const char * hostDomain = "example.com";
const int hostPort = 80;

const int BUTTON_PIN = 0;
const int LED_PIN = 13; //On board LED


// Define the array of leds
CRGB leds[NUM_LEDS];


// Timer vars
unsigned long timer[2] = {millis(), millis()};
// LED Indexs
int ledIndex[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Sequence vars
bool flashState = false;

//OSC
// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
//const IPAddress outIp(10,40,10,105);        // remote IP (not needed for receive)
const unsigned int outPort = 9999;          // remote port (not needed for receive)
const unsigned int localPort = 10000;        // local port to listen for UDP packets (here's where we send the packets)



OSCErrorCode error;
float ledState = 0;  


void setup()
{
  // Initilize hardware:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(50);
  AllOff();


  // Connect to the WiFi network (see function below loop)
  connectToWiFi(networkName, networkPswd);

  //UDP
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif

  digitalWrite(LED_PIN, LOW); // LED off
  Serial.print("Press button 0 to connect to ");
  Serial.println(hostDomain);
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == LOW)
  { // Check if button has been pressed
    while (digitalRead(BUTTON_PIN) == LOW)
      ; // Wait for button to be released

    digitalWrite(LED_PIN, HIGH); // Turn on LED
    requestURL(hostDomain, hostPort); // Connect to server
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }

  //OSC
//  ReadIncomingOSC();

//    DisplayConnectionCode(1);
//  Flash(500, 0, 5, CRGB::White);
ChaseLoop(250, 26, CRGB::White);
  
}

void ReadIncomingOSC() {
  OSCMessage msg;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) {
      msg.dispatch("/led", led);
      
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}

void led(OSCMessage &msg) {
  setColor(msg.getInt(0), msg.getInt(1), msg.getInt(2));
//  digitalWrite(BUILTIN_LED, ledState);
  Serial.print("/led: ");
  Serial.print(msg.getInt(0));
  Serial.print(" ");
  Serial.print(msg.getInt(1));
  Serial.print(" ");
  Serial.print(msg.getInt(2));
  Serial.println(" ");
}

void setColor(int r, int g, int b){
  fill_solid(leds, NUM_LEDS, CRGB(r,g,b));
  FastLED.show();
}

void connectToWiFi(const char * ssid, const char * pwd)
{
  int ledState = 0;

  printLine();
  Serial.println("Connecting to WiFi network: " + String(ssid));

  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED)
  {
    DisplayConnectionCode(0);
  }


  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //  DisplayConnectionCode(1);
  AllOff();
}

void requestURL(const char * host, uint8_t port)
{
  printLine();
  Serial.println("Connecting to domain: " + String(host));

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.println("Connected!");
  printLine();

  // This will send the request to the server
  client.print((String)"GET / HTTP/1.1\r\n" +
               "Host: " + String(host) + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000)
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
  client.stop();
}

void printLine()
{
  Serial.println();
  for (int i = 0; i < 30; i++)
    Serial.print("-");
  Serial.println();
}

void testPattern() {
  delay(500);
  for (int i = 5; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
    FastLED.show();
  }
  // Turn the LED on, then pause
  delay(500);
  for (int i = 5; i < NUM_LEDS; i++) {
    // Now turn the LED off, then pause
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void DisplayConnectionCode(int code) {
  switch (code) {
    case 0: // Connecting
      ChaseLoop(500, NUM_LEDS, CRGB::Blue);
      break;
    case 1: // Connection Established
      ChaseLoop(500, NUM_LEDS, CRGB::Green);
      break;
    case 2: // Connection Error
      ChaseLoop(500, NUM_LEDS, CRGB::Red);
      break;
  }
}

void ChaseLoop(int interval, int ledAmount, CRGB myColor) {
  CRGB targetColor = myColor;
  if (millis() - timer[0] > interval) {
    timer[0] = millis();

    // Set LED color
    //    leds[ledIndex[0]] = CRGB(0, 255, 255);
    leds[ledIndex[0]] = targetColor;
    FastLED.show();

    // Increment led index
    ledIndex[0]++;
    Serial.println(ledIndex[0]);

    // Loop to start
    if (ledIndex[0] > ledAmount) {
      AllOff();
      ledIndex[0] = 0;
    } else if (ledAmount = 0 && ledIndex[0] > NUM_LEDS) {
      AllOff();
      ledIndex[0] = 0;
    }
  }
}

void Flash(int interval, int startLED, int endLED, CRGB color) {
  CRGB targetColor = color;

  if (millis() - timer[1] > interval) {
    timer[1] = millis();

    if (!flashState) {
      for (int i = startLED; i < endLED; i++) {
        leds[i] = color;
        FastLED.show();
      }
      flashState = true;
    } else {
      for (int i = startLED; i < endLED; i++) {
        leds[i] = CRGB::Black;
        FastLED.show();
      }
      flashState = false;
    }

    // DEBUG
    //    Serial.print("Flash: ");
    //    Serial.print(flashState, DEC);
    //    Serial.println("");
  }
}

void AllOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    // Now turn the LED off, then pause
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}






//Dont mind me
