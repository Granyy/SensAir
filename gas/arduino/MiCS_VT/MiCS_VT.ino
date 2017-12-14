#include <Wire.h>
#include "MICS-VZ-89TE.h"

MICS_VZ_89TE sensor;

void setup() {

  Serial.begin(9600);
  sensor.begin();
  sensor.getVersion();
  Serial.print("Day: ");
  Serial.println(sensor.getDay());

  
}

void loop() {
  
sensor.readSensor();
Serial.print("CO2: ");
Serial.println(sensor.getCO2());
Serial.print("VOC: ");
Serial.println(sensor.getVOC());
Serial.print("Status: ");
Serial.println(sensor.getStatus());

delay(5000);

}
