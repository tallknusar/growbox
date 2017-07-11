bool timer(){
  DateTime now = RTC.now();
  int intHour = now.hour();
  int intMin = now.minute();
  if(timeHourON >= intHour && timeHourOFF < intHour){
      if(timeMinON >= intMin && timeMinOFF < intMin){
        statUpd("Lights on..");
        return true;
      }    
  }
}

