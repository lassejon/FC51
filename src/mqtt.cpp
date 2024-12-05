#include <PubSubClient.h>
#include <WiFi.h>
#include "time_handler.h"
#include "config.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void connectToMQTT()
{
    while (!mqttClient.connected())
    {
        Serial.print("Connecting to MQTT...");
        Serial.printf("Server: %s, Port: %d\n", MQTT_SERVER, MQTT_PORT);

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
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    connectToMQTT();
}

void publishDetection(String message)
{
    if (!mqttClient.connected())
    {
        connectToMQTT();
    }

    mqttClient.publish(MQTT_TOPIC, message.c_str());

    mqttClient.loop();
}