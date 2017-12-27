/******************************************************************************/
/*        @TITLE : Configuration.h                                            */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/



#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "driver/i2c.h"

//// I2C CONFIGURATIONS
#define I2C_SPEED 100000
#define I2C_SDA_PIN 22
#define I2C_SCL_PIN 26
#define I2C_INTERFACE I2C_NUM_0

void configure();

void I2C_config();


#endif