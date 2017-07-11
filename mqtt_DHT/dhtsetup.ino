void dhtsetup(){ 
  // Wait a few seconds between measurements.
  //delay(500);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  pidInput = t;
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    statUpd("Failed to read from DHT sensor!");
    //Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

/*
  Serial.println("Humidity: ");
  Serial.println(h);
  Serial.println("Temperature: ");
  Serial.println(t);
  */
 
  //char array to store values
  char temp[8];
  char hum[8];
  
  //convert float to char
  dtostrf(t, 6, 2, temp);
  dtostrf(h, 6, 2, hum);
  
  //publish values
  client.publish("growbox/temperature",temp);
  client.publish("growbox/humidity", hum);
  
  }
