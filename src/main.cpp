#include <Arduino.h>
#include "config.h"
#include "sensor_handler.h"
#include "storage.h"
#include "wifi_handler.h"
#include "time_handler.h"
#include "mqtt.h"

void setup()
{
  Serial.begin(115200);
  setupStorage();
  deleteLogFile();

  setupSensor();

  setupWiFi();
  if (isWiFiConnected())
  {
    Serial.println("WiFi connected");
    setupTime();
  }

  setupMQTT();

  Serial.println("Setup complete.");

  delay(3000);
}

void loop()
{
  if (isObjectDetected())
  {
    logDetection();
    readLogFile();
  }

  // delay(100); // Small delay to reduce loop load
}
