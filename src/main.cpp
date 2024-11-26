#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>

// Define pin for FC51 sensor
#define FC51 GPIO_NUM_33
#define FORMAT_LITTLEFS_IF_FAILED true

const char *filename = "/test.txt";
const char *dir = "/test";

char *combine_strings(const char *str1, const char *str2);

void createDir(fs::FS &fs, const char *path);
void readFile(fs::FS &fs, const char *path);
void writeFile(fs::FS &fs, const char *path, const char *message);
void appendFile(fs::FS &fs, const char *path, const char *message);

void setup()
{
  Serial.println("Starting...");

  // Initialize serial communication
  Serial.begin(115200);

  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
  {
    Serial.println("LittleFS Mount Failed");
    return;
  }

  Serial.println("LittleFS Mount Successful");

  // Set FC51 as input pin
  pinMode(FC51, INPUT);

  createDir(LittleFS, dir);
  writeFile(LittleFS, filename, "Creating file");
  appendFile(LittleFS, combine_strings(dir, filename), "Appending to file\n");
  readFile(LittleFS, combine_strings(dir, filename));
}

void loop()
{
  int sensorValue = digitalRead(FC51);

  Serial.println("Sensor value: " + String(sensorValue));

  // Reveresed logic
  if (sensorValue == 1) // Sensor detects something
  {
    Serial.println("There is something");
  }
  else // Sensor detects nothing
  {
    Serial.println("There is nothing");
  }

  readFile(LittleFS, combine_strings(dir, filename));

  // Delay for a second
  delay(1000);
}

char *combine_strings(const char *str1, const char *str2)
{
  // Calculate the length of the combined string
  size_t len1 = strlen(str1);
  size_t len2 = strlen(str2);
  size_t total_len = len1 + len2 + 1; // +1 for the null terminator

  // Allocate memory for the combined string
  char *combined = (char *)malloc(total_len);
  if (combined == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  // Copy the first string and concatenate the second string
  strcpy(combined, str1);
  strcat(combined, str2);

  return combined;
}

void createDir(fs::FS &fs, const char *path)
{
  Serial.printf("Creating Dir: %s\n", path);
  if (fs.mkdir(path))
  {
    Serial.println("Dir created");
  }
  else
  {
    Serial.println("mkdir failed");
  }
}

void readFile(fs::FS &fs, const char *path)
{
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory())
  {
    Serial.println("- failed to open file for reading");
    return;
  }

  Serial.println("- read from file:");
  while (file.available())
  {
    Serial.write(file.read());
  }
  file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    Serial.println("- file written");
  }
  else
  {
    Serial.println("- write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Appending to file bro: %s\r\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file)
  {
    Serial.println("- failed to open file for appending");
    return;
  }
  if (file.print(message))
  {
    Serial.println("- message appended");
  }
  else
  {
    Serial.println("- append failed");
  }
  file.close();
}