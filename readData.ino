void readData() {
    delay (rdDelay);
    sensorA = analogRead(analogInA);            
    sensorB = analogRead(analogInB);   
    time = millis() - time0;
         
    Serial.print(time);
    Serial.print(",");
    Serial.print(sensorA);    
    Serial.print(",");
    Serial.println(sensorB); 

    if(Serial.available()>0) {
    sRead = Serial.read();
    if (sRead == '%') {
      runState = false;
     }
    }
  }
