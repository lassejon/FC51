#include <Arduino.h>
#include "config.h"
#include "sensor_handler.h"
#include "storage.h"
#include "wifi_handler.h"
#include "time_handler.h"

void setup()
{
  Serial.begin(115200);
  setupStorage();
  setupSensor();

  setupWiFi();
  if (isWiFiConnected())
  {
    Serial.println("WiFi connected");
    setupTime();
  }

  Serial.println("Setup complete.");

  delay(3000);
}

void loop()
{
  if (isObjectDetected())
  {
    String timestamp = String(millis());
    String event = timestamp + ", Object passed";
    logEvent(event); // Log the event to LittleFS
    Serial.println(event);
  }

  // delay(100); // Small delay to reduce loop load
}
