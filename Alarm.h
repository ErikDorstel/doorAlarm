WiFiUDP udpAlarm;

void initAlarm() { udpAlarm.begin(9999); }

uint8_t packetBuffer[14];

void alarmWorker() {
  static uint32_t alarmTimer;

  int udpBytes=udpAlarm.parsePacket();
  if (udpBytes==14) {
    greenOn(); yellowOn(); alarmTimer=millis()+30000UL;;
    udpAlarm.read(packetBuffer,udpBytes);
    Serial.print("Alarm Packet received: ");
    for (int n=0;n<14;n++) { Serial.print(String(packetBuffer[n],HEX)); Serial.print(" "); } Serial.println();
    int slow=0, fast=0;
    for (int n=6;n<14;n++) {
      if (packetBuffer[n]==1) { slow=1; }
      if (packetBuffer[n]==2) { fast=1; } }
    if (slow==0 && fast==0) { redOff(); }
    else if (slow==1 && fast==0) { slowOn(); }
    else if (slow==0 && fast==1) { fastOn(); }
    else if (slow==1 && fast==1) { fastOn(); }
    greenOff(); yellowOff(); }

  else { for (int n=0;n<udpBytes;n++) { udpAlarm.read(); } }

  if (millis()>=alarmTimer) { greenOn(); } }
