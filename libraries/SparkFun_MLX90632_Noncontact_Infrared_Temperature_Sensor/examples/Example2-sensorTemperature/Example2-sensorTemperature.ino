/*
  Using the MLX90632 FIR Sensor
  By: Nathan Seidle
  SparkFun Electronics
  Date: December 21st, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14569

  This example shows how to read both the remote object temperature and the local sensor temperature.

  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the sensor onto the shield
  Serial.print it out at 9600 baud to serial monitor.
*/

#include <Wire.h>

#include "SparkFun_MLX90632_Arduino_Library.h"
MLX90632 myTempSensor;

void setup()
{
  Serial.begin(9600);
  Serial.println("MLX90632 Read Example");

  Wire.begin();

  myTempSensor.begin();
}

void loop()
{
  float objectTemp = myTempSensor.getObjectTempF(); //Get the temperature of the object we're looking at
  Serial.print("Object temperature: ");
  Serial.print(objectTemp, 2);
  Serial.print(" F");

  float sensorTemp = myTempSensor.getSensorTemp(); //Get the temperature of the sensor
  Serial.print(" Sensor temperature: ");
  Serial.print(sensorTemp, 2);
  Serial.print(" C");

  Serial.println();
}

