
#include <Wire.h>
#include "MICS-VZ-89TE.h" 
#include "MutichannelGasSensor.h"

MICS_VZ_89TE sensor;

#define SENSOR_ADDR     0X04        // default to 0x04
#define PRE_HEAT_TIME   0           // pre-heat time, 10-30 minutes is recommended
#define TIMER 10  //temps entre chaque mesure en seconde
#define BAUD 9600

void setup() {

  Serial.begin(BAUD);
  int count =0;
 
   
  sensor.begin();
  Serial.println("Sensor Mics_VZ power on");

  gas.begin(SENSOR_ADDR);   
  Serial.println("Sensor Grove power on");
  gas.powerOn(); 

  Serial.println("Pre-heat time before sending data");
  Serial.print(PRE_HEAT_TIME); Serial.println(":00");
  
    for(int i=60*PRE_HEAT_TIME; i>0; i--)
    {
        if (count == 30){
        Serial.print(i/60);
        Serial.print(":");
        Serial.println(i%60);
        count=0;
        }
        delay(1000);
        count++;
    }

    Serial.println("Ready for sending data");
    Serial.println("CO, NO2, CO2, VOC, TIME");
}

void loop() {

  int time_mesure =0;
  while(true) {  
    making_data_sensor(TIMER,time_mesure);
    time_mesure=time_mesure+TIMER;
  }

}

/******************************************************/

float making_data_sensor(int timer,int time_mesure)
{
  float c;
    
    c = gas.measure_CO();
    //Serial.print("CO,");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.print(",");

    c = gas.measure_NO2();
   // Serial.print("N02,");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.print(",");

  /* ********************************************** */

    sensor.readSensor();
    //Serial.print("CO2: ");
    Serial.print(sensor.getCO2());
    Serial.print(",");
    //Serial.print("VOC: ");
    Serial.print(sensor.getVOC());

    Serial.print(", ");
    Serial.println(time_mesure/60.0);

    delay(timer*1000);

 
    }
