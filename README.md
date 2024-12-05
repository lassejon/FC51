# ESP32 Detection System

# Hardware Components
- ESP32 DOIT DEVKIT V1 Board
- FC51 IR Obstacle Avoidance Sensor
- MicroSD Card Module (SPI)
- MicroSD Card
- Breadboard
- Jumper wires
- USB cable for programming

# Software/Libraries
- PubSubClient: MQTT client
- WiFi.h: WiFi connectivity
- LittleFS: File system
- NTPClient: Network time
- WiFiUDP: UDP for NTP
- SPI.h: SPI interface for SD card
- SD.h: SD card operations

# Connections
- FC51 VCC → 5V
- FC51 GND → GND
- FC51 OUT → GPIO 21 (configurable in config.h)
- SD Module VCC → 5V
- SD Module GND → GND
- SD Module MOSI → GPIO 23
- SD Module MISO → GPIO 19
- SD Module SCK → GPIO 18
- SD Module CS → GPIO 5

## Network Configuration

### Finding MQTT Server IP Address

#### Windows:
In cmd:
ipconfig

Look for IPv4 Address under active network adapter.

#### Mac:
In bash/zsh:
ifconfig

Look for inet under active interface (en0 for WiFi, en1 for Ethernet).

#### Linux:
In bash:
ip addr

Look for inet under active interface.

## Updating ESP32 Code
In mqtt.h:
#define MQTT_SERVER "YOUR_IP_HERE";

Upload code using Arduino IDE or PlatformIO.
