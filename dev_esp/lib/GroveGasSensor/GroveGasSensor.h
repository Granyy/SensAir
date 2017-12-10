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


#define ACK_VAL                            0x0
#define NACK_VAL                           0x1  

enum{CO, NO2, NH3, C3H8, C4H10, CH4, H2, C2H5OH};

class GroveGasSensor{

private:

    int __version;
    unsigned char dta_test[20];
    
public:

    //uint16_t res0[3];       //sensors res0
    //uint16_t res[3];        //sensors res
    //bool r0_inited;


    inline uint16_t get_addr_dta(uint8_t addrDev, uint8_t addrReg);
    inline uint16_t get_addr_dta(uint8_t addrDev, uint8_t addrReg, uint8_t addrDta);
    inline void write_i2c(uint8_t addrDev, uint8_t addrReg, uint8_t data);

    //void sendI2C(unsigned char dta); pour envoyer un nombre de bits définis ?
    // inline void write_i2c(uint8_t addrDev, uint8_t addrReg, uint8_t* data); len needed ?
    //int16_t readData(uint8_t cmd); pour lire plus de deux bits ?
    // inline uint8_t* get_addr_dta(uint8_t addrDev, uint8_t addrReg);
    //int16_t readR0(void);
    //int16_t readR(void);
    float calc_gas(int gas);
    
public:

    void begin(int address);
    void begin();
    //void powerOn(void);
    //void powerOff(void);
    
    float measure_CO(){return calc_gas(CO);}
    float measure_NO2(){return calc_gas(NO2);}
    float measure_NH3(){return calc_gas(NH3);}
    
    //float getR0(unsigned char ch);      // 0:CH3, 1:CO, 2:NO2
    //float getRs(unsigned char ch);      // 0:CH3, 1:CO, 2:NO2

    void led_on();    
    void led_off();
    
    void display_eeprom();
    //void factory_setting();
    unsigned char getVersion();
};

extern GroveGasSensor gas;

#endif