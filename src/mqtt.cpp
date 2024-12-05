#include <PubSubClient.h>
#include <WiFi.h>
#include "time_handler.h"

const char *mqtt_server = "192.168.1.3";
const int mqtt_port = 1883;
const char *mqtt_topic = "sensor/detections";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void connectToMQTT()
{
    while (!mqttClient.connected())
    {
        Serial.print("Connecting to MQTT...");
        Serial.printf("Server: %s, Port: %d\n", mqtt_server, mqtt_port);

        String clientId = "ESP32Client-" + String(random(0xffff), HEX);
        Serial.printf("ClientID: %s\n", clientId.c_str());

        if (mqttClient.connect(clientId.c_str()))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.printf("failed, rc=%d ", mqttClient.state());
            Serial.println(" retrying in 5 seconds");
            delay(5000);
        }
    }
}

void setupMQTT()
{
    mqttClient.setServer(mqtt_server, mqtt_port);
    connectToMQTT();
}

void publishDetection(String message)
{
    // Existing file logging code...

    // Add MQTT publishing
    if (!mqttClient.connected())
    {
        connectToMQTT();
    }

    mqttClient.publish(mqtt_topic, message.c_str());

    mqttClient.loop();
}