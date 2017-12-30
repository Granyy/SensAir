/******************************************************************************/
/*        @TITLE : GroveGasSensor.h                                           */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 10, 2017                                               */
/* @MODIFICATION : dec 10, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                 */
/******************************************************************************/



#ifndef __GROVEGASSENSOR_H__
#define __GROVEGASSENSOR_H__

#include <esp_log.h>
#include <string>
#include <iostream>
#include "sdkconfig.h"
#include <math.h>
#include "driver/i2c.h"

using namespace std;

#define DEFAULT_I2C_ADDR    0x04

#define ADDR_IS_SET             0          
#define ADDR_FACTORY_ADC_NH3    2
#define ADDR_FACTORY_ADC_CO     4
#define ADDR_FACTORY_ADC_NO2    6

#define ADDR_USER_ADC_HN3       8
#define ADDR_USER_ADC_CO        10
#define ADDR_USER_ADC_NO2       12
#define ADDR_IF_CALI            14          // IF USER HAD CALI

#define ADDR_I2C_ADDRESS        20

#define CH_VALUE_NH3            1
#define CH_VALUE_CO             2
#define CH_VALUE_NO2            3

#define CMD_ADC_RES0            1           // NH3
#define CMD_ADC_RES1            2           // CO
#define CMD_ADC_RES2            3           // NO2
#define CMD_ADC_RESALL          4           // ALL CHANNEL
#define CMD_CHANGE_I2C          5           // CHANGE I2C
#define CMD_READ_EEPROM         6           // READ EEPROM VALUE, RETURN UNSIGNED INT
#define CMD_SET_R0_ADC          7           // SET R0 ADC VALUE
#define CMD_GET_R0_ADC          8           // GET R0 ADC VALUE
#define CMD_GET_R0_ADC_FACTORY  9           // GET FACTORY R0 ADC VALUE
#define CMD_CONTROL_LED         10
#define CMD_CONTROL_PWR         11

#define ACK_VAL                 I2C_MASTER_ACK
#define NACK_VAL                I2C_MASTER_NACK

enum{CO, NO2, NH3};

class GroveGasSensor{

private:

    int __version;
    
public:
    inline uint16_t get_addr_dta(uint8_t addrDev, uint8_t addrReg);
    inline uint16_t get_addr_dta(uint8_t addrDev, uint8_t addrReg, uint8_t addrDta);
    inline void write_i2c(uint8_t addrDev, uint8_t addrReg, uint8_t data);
    inline void write_i2c(uint8_t addrDev, uint8_t* data);
    float calc_gas(int gas);
    
public:
    void power_on();
    void power_off();
    
    float measure_CO(){return calc_gas(CO);}
    float measure_NO2(){return calc_gas(NO2);}
    float measure_NH3(){return calc_gas(NH3);}
    
    float get_R0(int gas);      
    float get_Rs(int gas); 

    void led_on();    
    void led_off();
    
    void display_eeprom();
    void factory_setting(); // /!\ This function might be dangerous! 
    unsigned char get_version();
};

extern GroveGasSensor gas;

#endif
