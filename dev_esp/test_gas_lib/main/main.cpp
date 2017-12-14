#include <esp_log.h>
#include <iostream>
#include "sdkconfig.h"
#include <math.h>
#include "driver/i2c.h"
#include "GroveGasSensor.h"
#include "MicsGasSensor.h"
#include "linenoise/linenoise.h"
#include <sys/time.h>
#define SDA_PIN 22
#define SCL_PIN 26


using namespace std;

extern "C" {
   void app_main();
}

GroveGasSensor groveGasSensor;

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


void led_test() {
	groveGasSensor.led_on();
	vTaskDelay(500/ portTICK_RATE_MS);
	groveGasSensor.led_off();
	cout << "LED ON" << endl;
	vTaskDelay(2000/ portTICK_RATE_MS);
	groveGasSensor.led_on();
	cout << "LED OFF" << endl;
	vTaskDelay(2000/ portTICK_RATE_MS);
}

void power_test() {
	groveGasSensor.power_on();
	vTaskDelay(10000/ portTICK_RATE_MS);
	groveGasSensor.power_off();
}


void grove_test() {

	struct timeval tv;
	groveGasSensor.get_version();
	groveGasSensor.display_eeprom();
	cout << "R0" << endl;
	cout << "    CO" << "\t" << "\t  NO2" << "\t" << "\t  NH3" << endl;
	cout << " " << groveGasSensor.get_R0(CO) << "        " << groveGasSensor.get_R0(NO2) << "        " <<  groveGasSensor.get_R0(NH3) << endl;
	cout << "Rs" << endl;
	cout << "    CO" << "\t" << "\t  NO2" << "\t" << "\t  NH3" << endl;
	cout << " " << groveGasSensor.get_Rs(CO) << "        " << groveGasSensor.get_Rs(NO2) << "        " <<  groveGasSensor.get_Rs(NH3) << endl;
	vTaskDelay(500/ portTICK_RATE_MS);
	led_test();
	//power_test();
	vTaskDelay(1000/ portTICK_RATE_MS);
	

	int i = 15;
	while (1) {
		if (i == 15) {
			linenoiseClearScreen();
			i = 0;
			gettimeofday(&tv, nullptr);
			cout << "Time: " << tv.tv_sec << endl;
			cout << "    CO" << "\t" << "\t  NO2" << "\t" << "\t  NH3" << endl;
		}
		cout << " " << groveGasSensor.measure_CO() << "        " << groveGasSensor.measure_NO2() << "        " <<  groveGasSensor.measure_NH3() << endl;
		vTaskDelay(2000/ portTICK_RATE_MS);
		i++;
	}
	
}

void mics_test() {
	MicsGasSensor micsGasSensor;
	micsGasSensor.get_version();
	cout << "year: " << micsGasSensor.year << endl;
  	cout << "month: " << micsGasSensor.month << endl;
   	cout << "day: " << micsGasSensor.day << endl;
   	cout << "rev: " <<  micsGasSensor.rev << endl;
   	cout <<  "crc: " << micsGasSensor.crc << endl;
	while (1) {
		micsGasSensor.read_sensor();
		cout << "CO2: " << micsGasSensor.co2 << endl;
		cout << "VOC: " << micsGasSensor.voc << endl;
		vTaskDelay(2000/ portTICK_RATE_MS);
	}
}

void app_main(void)
{	
	I2C_config();
	mics_test();
	//grove_test();
} // app_main
