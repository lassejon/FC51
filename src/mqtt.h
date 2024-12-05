#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>

void setupMQTT();
void connectToMQTT();
void publishDetection(String message);

#endif // MQTT_H