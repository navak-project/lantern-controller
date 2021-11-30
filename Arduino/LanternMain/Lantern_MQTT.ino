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
  String audio = String() + mqtt_clientTopic + "/audio";

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == String(control)) {
    Serial.println("GOT CONTROL STRING");
    restart_esp32();
  }
  else if (String(topic) == String(ignite)) {
    OSCMessage msg(topic);

    int ctr = 0;
    while (getValue(messageTemp, ' ', ctr) != String("")) {
      String item = getValue(messageTemp, ' ', ctr);

      if (item.toInt() != 0) {
        msg.add((int)item.toInt());
      } else if (item.toFloat() != 0) {
        msg.add((float)item.toFloat());
      } else {
        msg.add(item.c_str());
      }

      ctr++;
    }

    SendToTeensy(msg);
  }
  else if (String(topic) == String(extinguish)) {
    OSCMessage msg(topic);
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
