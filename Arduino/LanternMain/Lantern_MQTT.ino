// Add your MQTT Broker IP address, example:
//tcp://192.168.1.13:1883

WiFiClient mqtt_client;
PubSubClient client(mqtt_client);

//const char* lanternHeader = "/lantern/";
//const char* controlString = "/control";
//const char* soundString = "/audio";
//
//String lanternControl;
//String lanternSound;

unsigned long mqttConnectionTimer = millis();

void MqttCallback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  //  char* lanternHeader = "/lantern/";
  //
  //  doConcat(lanternHeader, mqtt_panID, lanternHeader);
  //
  //  char* control = "/control";
  //
  //  doConcat(lanternHeader, control, control);

  String control = String() + mqtt_clientTopic + "/control";
  const char* audio = mqtt_clientTopic + "/audio";

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == String(control)) {
    Serial.println("GOT CONTROL STRING");
    restart_esp32();
  } else if (strcmp(topic, audio) == 0) {
    int ctr = 0;
    OSCMessage msg;

    while (String item = getValue(String(messageTemp), ' ', ctr) && item != "") {
      // address
      if (ctr == 0) {
        msg.setAddress(item.c_str());
      // arguments
      } else {
        msg.add(item.c_str());
      }

      // increment counter
      ctr++;
    }

    //  msg.add(messageTemp);
    SendToTeensy(msg);
  }
}

void LoopMQTT() {
  if (!client.connected()) {
    ConnectToMQTT();
  }

  client.loop();
}

void ConnectToMQTT() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    if (client.connect(esp_hostName_char)) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(mqtt_clientTopicWildCard);
      Serial.print("Subscribed to: ");
      Serial.println(mqtt_clientTopic);
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds");

      delay(5000);
    }
  }
}

void InitMQTT() {
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(MqttCallback);
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
