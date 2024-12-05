#ifndef CONFIG_H
#define CONFIG_H

// Pin definitions
#define FC51_PIN GPIO_NUM_33 // Flying Fish sensor
#define DEBOUNCE_DELAY 50    // Debounce time in ms

// LittleFS configuration
#define FORMAT_LITTLEFS_IF_FAILED true

// WiFi configuration
#define WIFI_AP_NAME "IoT_Device"

// File paths
#define LOG_FILE "/log.txt"

// MQTT configuration
#define MQTT_SERVER "192.168.1.4"
#define MQTT_PORT 1883
#define MQTT_TOPIC "sensor/detections"

// wifi
#define WIFI_SSID "a_cats_dick_hehe"
#define WIFI_PASSWORD "olatz_the_midget"
#define NTP_SERVER "pool.ntp.org"
#define TIME_ZONE_OFFSET 3600 // Example: 1 hour

#endif