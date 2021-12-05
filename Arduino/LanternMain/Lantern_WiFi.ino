#include <HTTPClient.h>
//#include <Arduino_JSON.h>

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
  
  SetNetworkInfo();
  
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(esp_ip);
  
  Register();
  UpdateStatus();
  
  AllOff();
}

void InitWifi() {
  connectToWiFi(networkName, networkPswd);
}

void SetNetworkInfo(){
  esp_macAddress = WiFi.macAddress();
  esp_ip = WiFi.localIP().toString();
  esp_hostName_String = WiFi.getHostname();
  esp_hostName_char = WiFi.getHostname();
}

void UpdateStatus(){
  HTTPClient http;
  DynamicJsonDocument doc(2048);
  
  String updateRequest = "{\"hostName\":\"" + esp_hostName_String + "\", \"macAddress\":\"" + esp_macAddress + "\", \"ipAddress\":\"" + esp_ip + "\"}";
  http.begin(updateStatusURL);
  Serial.print("HTTP Requesting to: ");
  Serial.println(updateStatusURL);
  http.addHeader("Content-Type", "application/json");

  Serial.print("HTTP UPDATE with: ");
  Serial.println(updateStatusURL);
  
  int httpResponseCode = http.PUT(updateRequest);
  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);


    deserializeJson(doc, http.getStream());
//    startUniverse = doc["startUniverse"];
//    mqtt_panID = doc["id"];
    
//    mqtt_panID = test;
//    Serial.println("#### API INFO RESPONSE ####");
//    Serial.print("startUniverse: ");
//    Serial.println(startUniverse);
//    Serial.print("panID: ");
//    Serial.println(mqtt_panID);

    payload = http.getString();
    Serial.println(payload);

//    doConcat(mqtt_topicParent, mqtt_panID, mqtt_clientTopic);
//
//    const char* wildcard = "/#";
//    doConcat(mqtt_clientTopic, wildcard, mqtt_clientTopicWildCard);
  }
  else {
    Serial.println("Error code: ");
    Serial.print(httpResponseCode);
    Serial.println();
  }

  http.end();

}

void Register() {
  HTTPClient http;
  DynamicJsonDocument doc(2048);
  
  String registerRequest = "{\"hostName\":\"" + esp_hostName_String + "\", \"macAddress\":\"" + esp_macAddress + "\", \"ipAddress\":\"" + esp_ip + "\"}";
  
  http.begin(registerUrl);
  Serial.print("HTTP Requesting to: ");
  Serial.println(registerUrl);
  http.addHeader("Content-Type", "application/json");

  Serial.print("HTTP POST with: ");
  Serial.println(registerRequest);
  
  int httpResponseCode = http.POST(registerRequest);
  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);


    deserializeJson(doc, http.getStream());
    startUniverse = doc["startUniverse"];
    mqtt_panID = doc["id"];
    
//    mqtt_panID = test;
    Serial.println("#### API INFO RESPONSE ####");
    Serial.print("startUniverse: ");
    Serial.println(startUniverse);
    Serial.print("panID: ");
    Serial.println(mqtt_panID);

    payload = http.getString();
    Serial.println(payload);

    doConcat(mqtt_topicParent, mqtt_panID, mqtt_clientTopic);

    const char* wildcard = "/#";
    doConcat(mqtt_clientTopic, wildcard, mqtt_clientTopicWildCard);
  }
  else {
    Serial.println("Error code: ");
    Serial.print(httpResponseCode);
    Serial.println();
  }

  http.end();

}
