WiFiUDP udpAlarm;

uint8_t ethMAC[6];

void initAlarm() {
  udpAlarm.begin(9999);
  uint64_t espid=ESP.getEfuseMac();
  ethMAC[0]=espid>>40&255; ethMAC[1]=espid>>32&255; ethMAC[2]=espid>>24&255;
  ethMAC[3]=espid>>16&255; ethMAC[4]=espid>>8&255; ethMAC[5]=espid>>0&255; }

uint8_t packetBuffer[14];

void alarmWorker() {
  static uint32_t alarmTimer;

  int udpBytes=udpAlarm.parsePacket();
  if (udpBytes==14) {
    greenOn(); yellowOn(); alarmTimer=millis()+90000UL;
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
    greenOff(); yellowOff();

    if (udpAlarm.beginPacket(udpAlarm.remoteIP(),9999)==1) {
      udpAlarm.write(ethMAC,6);
      udpAlarm.endPacket();
      Serial.println("Reply Packet sent."); } }

  if (millis()>=alarmTimer) { greenOn(); } }
