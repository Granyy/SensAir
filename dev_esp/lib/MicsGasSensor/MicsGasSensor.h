/******************************************************************************/
/*        @TITLE : MicsGasSensor.h                                            */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 10, 2017                                               */
/* @MODIFICATION : dec 10, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#ifndef __MICSGASSENSOR_H__

#define __MICSGASSENSOR_H__

#include <esp_log.h>
#include <string>
#include <iostream>
#include "sdkconfig.h"
#include <math.h>
#include "driver/i2c.h"


#define MICS_VZ_89TE_ADDR                  0x70
#define MICS_VZ_89TE_ADDR_CMD_GETSTATUS	   0x0C
#define MICS_VZ_89TE_DATE_CODE             0x0D

#define ACK_VAL                 0x0
#define NACK_VAL                0x1  

using namespace std;

class MicsGasSensor {
    
public:
    MicsGasSensor();
    float get_CO2();
    float get_VOC();
    float get_year();
    float get_month();
    float get_day();
    float get_rev();
    float get_crc();
    float get_status();
    
    float co2;
    float voc;
    float status;
    
    float year ;
    float month;
    float day;
    float rev;
    float crc;
    
    bool begin();
    void read_sensor();
    void get_version();
    
    
private:
    
    uint8_t   _i2caddr;
    void read_data(uint8_t addrDev, uint8_t addrReg, uint8_t data[]);

};

extern MicsGasSensor mics;

#endif
