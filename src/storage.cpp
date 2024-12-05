#include "storage.h"
#include "config.h"
#include "time_handler.h"
#include "mqtt.h"

uint32_t currentDetectionNumber = 0;

void setupStorage()
{
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
    {
        Serial.println("LittleFS Mount Failed");
        while (true)
        {
        }
    }

    if (!LittleFS.exists(LOG_FILE))
    {
        File file = LittleFS.open(LOG_FILE, FILE_WRITE);
        if (file)
        {
            file.println("timestamp,detectionNumber");
            file.close();
            currentDetectionNumber = 0;
        }
    }
    else
    {
        File file = LittleFS.open(LOG_FILE, FILE_READ);
        if (file)
        {
            String lastLine;
            while (file.available())
            {
                String line = file.readStringUntil('\n');
                if (line.length() > 0)
                {
                    lastLine = line;
                }
            }
            file.close();

            if (lastLine.length() > 0)
            {
                int commaIndex = lastLine.lastIndexOf(',');
                if (commaIndex != -1)
                {
                    currentDetectionNumber = lastLine.substring(commaIndex + 1).toInt();
                }
            }
        }
    }

    Serial.printf("Storage setup complete. Last detection number: %d\n", currentDetectionNumber);
}

void logDetection()
{
    File file = LittleFS.open(LOG_FILE, FILE_APPEND);
    if (!file)
    {
        Serial.println("Failed to open log file");
        return;
    }

    currentDetectionNumber++;
    String timestamp = getCurrentTime();
    String logLine = timestamp + "," + String(currentDetectionNumber);

    file.println(logLine);
    publishDetection(logLine);

    file.close();

    Serial.println("Logged: " + logLine);
}

void readLogFile()
{
    File file = LittleFS.open(LOG_FILE, FILE_READ);
    if (!file)
    {
        Serial.println("Failed to open log file for reading");
        return;
    }

    Serial.println("\n--- Log File Contents ---");
    while (file.available())
    {
        String line = file.readStringUntil('\n');
        Serial.println(line);
    }
    Serial.println("--- End of File ---\n");

    file.close();
}

void deleteLogFile()
{
    if (LittleFS.remove(LOG_FILE))
    {
        Serial.println("Log file deleted");
        currentDetectionNumber = 0;
    }
    else
    {
        Serial.println("Failed to delete log file");
    }
}