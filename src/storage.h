#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <LittleFS.h>

void setupStorage();
void logEvent(const String &event);

#endif // STORAGE_H
