// Add your MQTT Broker IP address, example:
//tcp://192.168.1.13:1883

WiFiClient mqtt_client;
PubSubClient client(mqtt_client);

unsigned long mqttConnectionTimer = millis();

void MqttCallback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  String control = "/lantern/" + String(mqtt_panID) + "/control";
  String audio = "/lantern/" + String(mqtt_panID) + "/audio";

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  Serial.println(control.c_str());
  Serial.println(topic);
  if (topic.c_string() == control.c_str()) {
    Serial.println("GOT CONTROL STRING");
    restart_esp32();
  } else if (topic == audio.c_str()) {
    OSCMessage msg(messageTemp.c_str());
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
      client.subscribe(mqtt_clientTopic);
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
