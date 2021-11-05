#include <HTTPClient.h>
//#include <Arduino_JSON.h>
#include <ArduinoJson.h>

const String local_pc_ip = "192.168.1.195";
const String local_pc_port = "8080";

String serverName = "http://" + local_pc_ip + ":" + local_pc_port + "/";


// SAVE BY MAC ADDRESS

void printLine()
{
  Serial.println();
  for (int i = 0; i < 30; i++)
    Serial.print("-");
  Serial.println();
}

void connectToWiFi(const char * ssid, const char * pwd)
{
  int ledState = 0;

  printLine();
  Serial.println("Connecting to WiFi network: " + String(ssid));
  //  WiFi.setHostname(hostname.c_str());
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED)
  {
    DisplayConnectionCode(0);
  }
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Register();

  //  DisplayConnectionCode(1);
  AllOff();
}

void InitWifi() {
  connectToWiFi(networkName, networkPswd);

  //  Serial.println(WiFi.macAddress());
}


void Register() {
  HTTPClient http;
  String registerUrl = serverName + "api/lanterns/register/";
  
  //  StaticJsonDocument<200> doc;
  DynamicJsonDocument doc(2048);
  
  http.begin(registerUrl);
  Serial.println(registerUrl);
  http.addHeader("Content-Type", "application/json");

  // Data to send with HTTP POST
  // Send HTTP POST request
  String mac = WiFi.macAddress();
  String ip = WiFi.localIP().toString();
  String requestQuote = "{\"macAddress\":\"" + mac + "\", \"ipAddress\":\"" + ip + "\"}";
  int httpResponseCode = http.POST(requestQuote);
  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.println("HTTP Response code: ");
    Serial.println(httpResponseCode);

    //    char json[] = http.getString();
    //    DeserializationError error = deserializeJson(doc, json);

//    if (error) {
//      Serial.print(F("deserializeJson() failed: "));
//      Serial.println(error.f_str());
//      //      return;
//    }
    deserializeJson(doc, http.getStream());
//    Serial.println(doc);
    int test = doc["startUniverse"];
    Serial.print("RECEIVED UNIVERSE: ");
    Serial.println(test);
    

    payload = http.getString();
    Serial.println(payload);

    //users = [payload];
    //Serial.println(users);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

}
