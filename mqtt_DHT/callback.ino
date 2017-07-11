void callback(char* topic, byte* payload, unsigned int length) {

  //Preform an action when a subscribed topic gets a mesasge.

  
  //Set temp setpoint  
  if (strcmp(topic, "growbox/temperature/set") ==0){
    String s = String((char*)payload);
    int intTemp = s.toInt();   
    pidSetpoint = intTemp;
    statUpd("Temp set fra MQTT: " + String(intTemp)); 
  }

  //Set pid values
  if (strcmp(topic, "growbox/pid/p/set") ==0){
    String s = String((char*)payload);
    int intP = s.toInt();   
    Kp = intP;
    statUpd(("P set fra MQTT: " + String(intP)));
    
  }

  if (strcmp(topic, "growbox/pid/i/set") ==0){
    String s = String((char*)payload);
    int intI = s.toInt();   
    Ki = intI;
    statUpd(("I set fra MQTT: " + String(intI)));
  }

  if (strcmp(topic, "growbox/pid/d/set") ==0){
    String s = String((char*)payload);
    int intD = s.toInt();   
    Kd = intD;
    statUpd(("D set fra MQTT: " + String(intD)));
  }

  if (strcmp(topic, "growbox/time/hour/on/set") ==0){
    String s = String((char*)payload);
    int value = s.toInt();   
    timeHourON = value;
    statUpd(("Hour ON from MQTT: " + String(timeHourON)));
  }

  if (strcmp(topic, "growbox/time/hour/off/set") ==0){
    String s = String((char*)payload);
    int value = s.toInt();   
    timeHourOFF = value;
    statUpd(("Hour OFF form MQTT: " + String(timeHourOFF)));
  }

  if (strcmp(topic, "growbox/time/min/on/set") ==0){
    String s = String((char*)payload);
    int value = s.toInt();   
    timeMinON = value;
    statUpd(("Min ON from MQTT: " + String(timeMinON)));
  }

  if (strcmp(topic, "growbox/time/min/off/set") ==0){
    String s = String((char*)payload);
    int value = s.toInt();   
    timeMinOFF = value;
    statUpd(("Min OFF form MQTT: " + String(timeMinOFF)));
  }

  //Read temp from eeprom and publish to get
  if (strcmp(topic, "growbox/temperature/getReq") ==0){
    //tempGet();  
    getIntSetting("growbox/temperature/get", pidSetpoint, "Temp set from MQTT: ");
  }
  
  if (strcmp(topic, "growbox/save") ==0){
    saveSettings();
  }

  if (strcmp(topic, "growbox/pid/p/getReq") ==0){
    //getP();
    getIntSetting("growbox/pid/p/get", Kp, "P set from MQTT");
  }

  if (strcmp(topic, "growbox/pid/i/getReq") ==0){
    //getI();
    getIntSetting("growbox/pid/i/get", Ki, "I set from MQTT");
  }

  if (strcmp(topic, "growbox/pid/d/getReq") ==0){
    //getD();
    getIntSetting("growbox/pid/d/get", Kd, "D set from MQTT");
  }

  if (strcmp(topic, "growbox/time/getReq") ==0){
    getTime();
  }

  if(strcmp(topic, "growbox/time/hour/on/getReq") ==0){
    getIntSetting("growbox/time/hour/on/get", timeHourON, "Time on from MQTT: ");
  }
}

//void setSetting(char* topic,char* payload, String equalsTopic, String text, int setValue){
//    if(strcmp(topic, equalsTopic) ==0){
//      String s = String((char*)payload);
//      int inValue = s.toInt();
//      setValue = inValue;
//    }
//  }

