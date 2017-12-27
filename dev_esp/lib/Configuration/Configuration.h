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
#include "driver/ledc.h"

//// I2C CONFIGURATIONS
#define I2C_SPEED       100000
#define I2C_SDA_PIN     22
#define I2C_SCL_PIN     26
#define I2C_INTERFACE   I2C_NUM_0

//// TIMER CONFIGURATIONS
#define LEDRGB_TIMER    LEDC_TIMER_0
#define LEDRGB_MODE     LEDC_HIGH_SPEED_MODE
#define LEDRGB_FREQ     5000
#define LEDR_GPIO       (18)
#define LEDG_GPIO       (23)
#define LEDB_GPIO       (19)
#define LEDR_CHANNEL    LEDC_CHANNEL_0
#define LEDG_CHANNEL    LEDC_CHANNEL_1
#define LEDB_CHANNEL    LEDC_CHANNEL_2
#define LEDC_TEST_DUTY  (1000)

void configure();

void I2C_config();
void Timer_config();


#endif