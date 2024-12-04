#include "storage.h"
#include "config.h"

void setupStorage()
{
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
    {
        Serial.println("LittleFS Mount Failed");
        while (true)
        {
        }
    }
    Serial.println("LittleFS Mount Successful");
}

void logEvent(const String &event)
{
    File file = LittleFS.open(LOG_FILE, FILE_APPEND);
    if (!file)
    {
        Serial.println("Failed to open log file");
        return;
    }

    file.println(event);
    file.close();
}
