/*
 Publishing in the callback

  - connects to an MQTT server
  - subscribes to the topic "inTopic"
  - when a message is received, republishes it to "outTopic"

  This example shows how to publish messages within the
  callback function. The callback function header needs to
  be declared before the PubSubClient constructor and the
  actual callback defined afterwards.
  This ensures the client reference in the callback function
  is valid.

*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <Stepper.h>
#include <PID_v1.h>
#include "DHT.h"
#include <Wire.h>
#include "RTClib.h"
#include <stdlib.h>

#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTPIN 2     // what digital pin we're connected to

DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 RTC;
long previousMillis = 0;
long interval = 1000;

//PID
double pidSetpoint, pidInput, pidOutput;
//pidSetpoint = EEPROM.read(0);
double Kp=2, Ki=5, Kd=1;
PID myPID(&pidInput, &pidOutput, &pidSetpoint, Kp, Ki, Kd, REVERSE);
//myPID.SetTunings(Kp, Ki, Kd);
int lastOut = 0;
float pos = 0;
const int buttonPin = 3;
volatile int buttonState = 0;
boolean stepStop = true;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// Network
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 111);
IPAddress server(192, 168, 1, 101);
EthernetClient ethClient;

//MQTT
// Callback function header
void callback(char* topic, byte* payload, unsigned int length);
PubSubClient client(server, 1883, callback, ethClient);

// Stepper
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

//Reconnect if not connected
long lastReconnectAttempt = 0;

int timeHourON;
int timeMinON;
int timeHourOFF;
int timeMinOFF;

boolean reconnect() {
  if (client.connect("arduinoClient")) {
    // Once connected, publish an announcement...
    client.publish("outTopic","hello world");
    // ... and resubscribe
    client.subscribe("inTopic");
  }
  return client.connected();
}

void setup()
{  
  Serial.begin(9600);
  Serial.println("SETUP!");
  Ethernet.begin(mac, ip);
  delay(1500);
  lastReconnectAttempt = 0;

  //Load Settings
  loadSettings();

  //Set PID tunings
  myPID.SetTunings(Kp, Ki, Kd);
  
  //Start DHT
  dht.begin();
  
  //Connect to broker and subscribe to topics.
  if (client.connect("arduGrowbox")) {
    subscribeToTopics();   
  }
  if(client.connected()){
      statUpd("MQTT client Connected");
      statUpd("####GROWBOX####");
      //Serial.println("MQTT client Connected");    
    }
    //Publish settings to MQTT
    statUpd("Publishing settings");
    //Serial.println("Publishing settings");
    tempGet();
    getP();
    getI();
    getD();
//    getIntSetting("growbox/temperature/get", pidSetpoint, "Temp set from MQTT: ");
//    getIntSetting("growbox/pid/p/get", Kp, "P set from MQTT");
//    getIntSetting("growbox/pid/i/get", Ki, "I set from MQTT");
//    getIntSetting("growbox/pid/d/get", Kd, "D set from MQTT");

    //Stepper motor
    // set the speed at 60 rpm:
    myStepper.setSpeed(5);
    //Define stepEnd pin
    pinMode(buttonPin, INPUT);
    

    //turn the PID on
    myPID.SetOutputLimits(0, 100);
    myPID.SetMode(AUTOMATIC);  

    //Step end
      attachInterrupt(1, brakeStep, FALLING);
      //Serial.println("Waiting for end switch...");
      statUpd("Initializing stepper motor...");
      stepSetup();
      myStepper.step(-20);

    //RTC
    Wire.begin();
    RTC.begin();
    if (! RTC.isrunning()) {
      statUpd("RTC is NOT running!");
      //Serial.println("RTC is NOT running!");
      // following line sets the RTC to the date & time this sketch was compiled
      RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
}

void loop()
{
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected

    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
    dhtsetup();
    }
    myPID.Compute();
    
//    Serial.print("Input: ");
//    Serial.print(pidInput);
//    Serial.print(" Setpoint: ");
//    Serial.print(pidSetpoint);
//    Serial.print(" Output: ");
//    Serial.println(pidOutput);


    //RTC
//    DateTime now = RTC.now(); 
//    Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(' ');
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
//    Serial.println(); 
//    delay(1000);
//  Serial.println(__TIME__);

   
    stepRun(pidOutput);
      
    client.loop();   
  } 
}
