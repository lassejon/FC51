#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <LittleFS.h>

void setupStorage();
void logDetection();
void readLogFile();
void deleteLogFile();

#endif // STORAGE_H
