/******************************************************************************/
/*        @TITLE : Configuration.c                                            */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "Configuration.h"


void configure() {
	ISR_config();
	I2C_config();
	Timer_config();
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



void ISR_config() {
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en =  GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_POSEDGE);
    gpio_install_isr_service(0);
}
