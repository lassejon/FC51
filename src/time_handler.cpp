#include <NTPClient.h>
#include <WiFiUdp.h>
#include "config.h"
#include "time_handler.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, TIME_ZONE_OFFSET);

void setupTime()
{
    timeClient.begin();
    timeClient.update();
}

String getCurrentTime()
{
    timeClient.update();
    return timeClient.getFormattedTime();
}