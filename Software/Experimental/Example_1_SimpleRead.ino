#include "AS6212.h"
#include <Wire.h>

AS6212 sensor;

void setup(){

  Wire.begin();
  Serial.begin(115200);

  Serial.println("Starting Sensor, here goes nothing...");
  delay(500);

  if(sensor.begin() == true){
    
    Serial.println("Beginning");
  
  }

  else{

    Serial.println("Well here we are, feeling foolish are we?");
    while(1);
    
  }
  
}

void loop(){

  float tempC = sensor.readTempC();
  float tempF = sensor.readTempF();

  Serial.println();
  Serial.print("Temperature (°C): ");
  Serial.println(tempC, 6);
  Serial.print("Temperature(°F): ");
  Serial.println(tempF, 6);
  Serial.print("Low Temperature Limit: ");
  Serial.println(sensor.getTLow());
  Serial.print("High Temperature Limit: ");
  Serial.println(sensor.getTHigh());

  //sensor.setTLow(75);
  //sensor.setTHigh(48);

//  Serial.print("Low Temperature Limit: ");
//  Serial.println(sensor.getTLow());
//  Serial.print("High Temperature Limit: ");
//  Serial.println(sensor.getTHigh());

  Serial.print("\nConfiguration Register: ");
  Serial.println(sensor.readConfig(), HEX);

  Serial.println("\nTrying to set configuration register...");
  Serial.print("New Configuration Register: ");
  sensor.setConfig(SLEEPSS);
  Serial.println(sensor.readConfig(), HEX);

  
  
  delay(1000);
  
}
