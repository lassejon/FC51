#include "sensor_handler.h"
#include "config.h"

volatile bool object_detected = false;
unsigned long lastInterruptTime = 0;

void IRAM_ATTR handleInterrupt()
{
    unsigned long currentTime = millis();

    if ((currentTime - lastInterruptTime) > DEBOUNCE_DELAY)
    {
        bool currentState = digitalRead(FC51_PIN);
        if (currentState == LOW) // Reflective signal interrupted
        {
            object_detected = true;
        }

        lastInterruptTime = currentTime;
    }
}

void setupSensor()
{
    pinMode(FC51_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(FC51_PIN), handleInterrupt, CHANGE);
}

bool isObjectDetected()
{
    if (object_detected)
    {
        object_detected = false;

        return true;
    }

    return false;
}
