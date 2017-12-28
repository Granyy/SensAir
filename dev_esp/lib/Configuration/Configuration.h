/******************************************************************************/
/*        @TITLE : Configuration.h                                            */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/



#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <stdio.h>
#include "driver/i2c.h"
#include "driver/ledc.h"
#include "driver/gpio.h"

//// I2C CONFIGURATIONS
#define I2C_SPEED       100000
#define I2C_SDA_PIN     GPIO_NUM_22
#define I2C_SCL_PIN     GPIO_NUM_26
#define I2C_INTERFACE   I2C_NUM_0

//// TIMER CONFIGURATIONS
#define LEDRGB_TIMER    LEDC_TIMER_0
#define LEDRGB_MODE     LEDC_HIGH_SPEED_MODE
#define LEDRGB_FREQ     5000
#define LEDR_GPIO       GPIO_NUM_18
#define LEDG_GPIO       GPIO_NUM_23
#define LEDB_GPIO       GPIO_NUM_19
#define LEDR_CHANNEL    LEDC_CHANNEL_0
#define LEDG_CHANNEL    LEDC_CHANNEL_1
#define LEDB_CHANNEL    LEDC_CHANNEL_2

//// ISR CONFIGURATIONS
#define GPIO_INPUT_IO_0     GPIO_NUM_4
#define GPIO_INPUT_PIN_SEL  (1<<GPIO_INPUT_IO_0)

void configure();

void I2C_config();
void Timer_config();
void ISR_config();


#endif
