//Run stepper 180deg max
void stepRun(int pidOutput){
  int out = 0;
  if(pidOutput >= lastOut && pos < 100){
  out = abs(pidOutput - lastOut);
  pos = pos + out;
  if(out > 0){
      //statUpd("OUT: " + String(out));
    myStepper.step(out);
  }
  }else if(pidOutput < lastOut && pos > 0) {
    out = abs(pidOutput - lastOut) * -1;
    pos = pos + out;   
    myStepper.step(out);
  }

 lastOut = pidOutput;
//  Publish speed to MQTT
  char charPos[8];
  dtostrf(pos, 6, 2, charPos);
  client.publish("growbox/stepper/speed", charPos);
  }

//Run stepper in setup to find 0 point
void stepSetup(){
  buttonState = digitalRead(buttonPin); 
  while(stepStop){
    myStepper.step(1);      
  }
  
}
void brakeStep(){
  statUpd("Stepper motor ready.");
  delay(500);
  stepStop = false;
}
