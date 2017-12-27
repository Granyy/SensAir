/******************************************************************************/
/*        @TITLE : Configuration.c                                            */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "Configuration.h"


void configure() {
	I2C_config();
}

void I2C_config() {
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = (gpio_num_t)I2C_SDA_PIN;
	conf.scl_io_num = (gpio_num_t)I2C_SCL_PIN;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = I2C_SPEED;
	i2c_param_config(I2C_INTERFACE, &conf);
	i2c_driver_install(I2C_INTERFACE, I2C_MODE_MASTER, 0, 0, 0);
}


void Timer_config() {
	ledc_timer_config_t ledc_timer;
	ledc_timer.bit_num = LEDC_TIMER_10_BIT,
	ledc_timer.freq_hz = LEDRGB_FREQ,                      
	ledc_timer.speed_mode = LEDRGB_MODE;
	ledc_timer.timer_num = LEDRGB_TIMER;
    ledc_timer_config(&ledc_timer);
}