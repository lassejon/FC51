#include <WiFi.h>
#include "config.h"
#include "wifi_handler.h"

void setupWiFi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi Connected");
}

bool isWiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}