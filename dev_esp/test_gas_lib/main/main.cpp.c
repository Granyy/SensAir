#include <esp_log.h>
#include <string>
#include <iostream>
#include "sdkconfig.h"
#include <math.h>
#include "driver/i2c.h"
#include "GroveGasSensor/GroveGasSensor.h"

#define SDA_PIN 22
#define SCL_PIN 26


using namespace std;

extern "C" {
   void app_main();
}



void I2C_config() {
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = (gpio_num_t)SDA_PIN;
	conf.scl_io_num = (gpio_num_t)SCL_PIN;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 100000;
	i2c_param_config(I2C_NUM_0, &conf);
	i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
}


void grove_test() {
	NULL;
}

void app_main(void)
{
	grove_test();
} // app_main
