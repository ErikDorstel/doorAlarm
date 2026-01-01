const char *apSSID="xxx";
const char *apPW="xxx";

#include "LED.h"
#include "WLAN.h"
#include "Alarm.h"

void setup() {
  Serial.begin(115200);
  initLED();
  initWLAN();
  initAlarm(); }

void loop() { ledWorker(); wlanWorker(); alarmWorker(); }
