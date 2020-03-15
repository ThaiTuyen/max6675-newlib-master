#include <Arduino.h>
#include "max6675Plus.h"

#define SCLK 12
#define MSIO 13
#define Sensor1_cs 11
#define Sensor2_cs 10

SubSPI config(SCLK,MSIO);
MAX6675 sensor1 (Sensor1_cs,config);
MAX6675 sensor2 (Sensor2_cs,config);

void setup() {
  Serial.begin(9600);
  Serial.println("start");
}

void loop() {
 Serial.print("sensor 1: ");
 Serial.println(sensor1.readCelsius());
 delay(10);
 Serial.print("sensor 2: ");
 Serial.println(sensor2.readCelsius());
 delay(1000);
}
