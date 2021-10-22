#include <WiFi.h>
#include <FastLED.h>

#define NUM_LEDS 5
#define DATA_PIN 19

// WiFi network name and password:
const char * networkName = "Silva-WIFI";
const char * networkPswd = "silvaFTW";

// Internet domain to request from:
const char * hostDomain = "example.com";
const int hostPort = 80;

const int BUTTON_PIN = 0;
const int LED_PIN = 13;


// Define the array of leds
CRGB leds[NUM_LEDS];

// Timer vars
unsigned long timer1 = millis();

// LED Indexs
int ledIndex[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void setup()
{
  // Initilize hardware:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(50);


  // Connect to the WiFi network (see function below loop)
  connectToWiFi(networkName, networkPswd);

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

  //  testPattern();
  DisplayConnectionCode(0);
}

void connectToWiFi(const char * ssid, const char * pwd)
{
  int ledState = 0;

  printLine();
  Serial.println("Connecting to WiFi network: " + String(ssid));

  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED)
  {
    // Blink LED while we're connecting:
    digitalWrite(LED_PIN, ledState);
    ledState = (ledState + 1) % 2; // Flip ledState

    delay(500);
    Serial.print(".");
  }


  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
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
      ChaseLoop(500, 5, CRGB::Green);
      break;
    case 1: // Connection Established
      break;
    case 2: // Connection Error
      break;
    default:
      break;
  }
}

void ChaseLoop(int reqTime, int ledAmount, CRGB myColor) {
  CRGB targetColor = myColor;
  if (millis() - timer1 > reqTime) {
    timer1 = millis();

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


void AllOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    // Now turn the LED off, then pause
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}






//Dont mind me
