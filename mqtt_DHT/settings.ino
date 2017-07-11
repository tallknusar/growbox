//Load settings
void loadSettings(){
  statUpd("Loading settings...");
  pidSetpoint = EEPROM.read(0);
  Kp =(double) EEPROM.read(1);
  Ki =(double) EEPROM.read(2);
  Kd =(double) EEPROM.read(3);
  delay(500);
  statUpd("Settings loaded.");
}

//Save settings
void saveSettings(){
  statUpd("Saving settings...");
  EEPROM.update(0, pidSetpoint);
  EEPROM.update(1, Kp);
  EEPROM.update(2, Ki);
  EEPROM.update(3, Kp);
  delay(500);
  statUpd("Settings saved.");
}

//Publish Settings

void getP(){
    char p[8];
    String str = String(Kp);
    str.toCharArray(p,Kp);
    client.publish("growbox/pid/p/get",p);
    statUpd(("MQTT get P: " + String(Kp)));
    delay(200);
}

void getI(){
  char i[8];
    String str = String(Ki);
    str.toCharArray(i,Ki);
    client.publish("growbox/pid/i/get",i);
    statUpd(("MQTT get I: " + String(Ki)));
    delay(200);
}

void getD(){
  char d[8];
    String str = String(Kd);
    str.toCharArray(d,Kd);
    client.publish("growbox/pid/d/get",d);
    statUpd(("MQTT get D: " + String(Kd)));
    delay(200);
}

void tempGet(){
    char temp[8];
    String str = String(pidSetpoint);
    str.toCharArray(temp,pidSetpoint);
    client.publish("growbox/temperature/get",temp);
    statUpd(("MQTT get pidSetpoint: " + String(temp)));
   
}

void getIntSetting(char topic, double setting, String text){
    char settingArray[8];
    String str = String(setting);
    str.toCharArray(settingArray,setting);
    client.publish(topic, settingArray);
    statUpd((text + String(setting)));
    
}

void getTime(){
    DateTime now = RTC.now();
    int intMin = now.minute();
    int intHour = now.hour();
    int intSek = now.second();
    char timeArray[16];
    String str = (String(intHour) + ":" + String(intMin) + ":" + String(intSek));
    str.toCharArray(timeArray,16);
    client.publish("growbox/time/get",timeArray);
    statUpd("Arduino time: " + String(timeArray));
    
}

//void getOnTimeHour(){
//    char charArray[8];
//    String str = String(timeHourON);
//    str.toCharArray(temp,timeHourON);
//    client.publish("growbox/temperature/get",temp);
//    statUpd(("MQTT get pidSetpoint: " + String(temp)));
//    delay(200);
//}

//Publish status to MQTT
void statUpd(String str){
    char stat[32];
    str.toCharArray(stat,32);
    Serial.println(str);
    client.publish("growbox/status",stat);
}

