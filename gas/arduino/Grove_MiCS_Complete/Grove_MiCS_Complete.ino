// Calibration code for Grove - Multichannel Gas Sensor
// Note that it need 10 minutes pre-heat before calibration


#include <Wire.h>
#include "MutichannelGasSensor.h"

#define SENSOR_ADDR     0X04        // default to 0x04
#define PRE_HEAT_TIME   1           // pre-heat time, 10-30 minutes is recommended
#define CALIBRATION   0           // 0 or 1 if you want a calibration

void setup()
{
    Serial.begin(115200);
    gas.begin(SENSOR_ADDR);   // set the adress
    
    Serial.println("power on");
    gas.powerOn(); //set the power of the heater

    Serial.println("Ro: ");
   gas.getR0(0);
   gas.getR0(1);
   gas.getR0(2);

    if (CALIBRATION){
       
       Serial.println("pre-heat for calibration");
    for(int i=60*PRE_HEAT_TIME; i>=0; i--)
    {
        Serial.print(i/60);
        Serial.print(":");
        Serial.println(i%60);
        delay(1000);
    }
    
    Serial.println("Begin to calibrate...");
    gas.doCalibrate();
    Serial.println("Calibration ok");
    
    Serial.println("New Ro: ");
    gas.getR0('0');
    gas.getR0('1');
    gas.getR0('2');
    
    gas.display_eeprom();
    }
   
}

void loop()
{
    making_data_sensor(5);
}



void making_data_sensor(int timer)
{
  float c;
  
    c = gas.measure_NH3();
    Serial.print("The concentration of NH3 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_CO();
    Serial.print("The concentration of CO is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_NO2();
    Serial.print("The concentration of NO2 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_C3H8();
    Serial.print("The concentration of C3H8 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_C4H10();
    Serial.print("The concentration of C4H10 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_CH4();
    Serial.print("The concentration of CH4 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_H2();
    Serial.print("The concentration of H2 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_C2H5OH();
    Serial.print("The concentration of C2H5OH is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    delay(timer*1000);
    Serial.println("...");
}


