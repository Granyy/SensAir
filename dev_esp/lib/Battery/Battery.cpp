/******************************************************************************/
/*        @TITLE : Battery.h                                                  */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : jan 10, 2017                                               */
/* @MODIFICATION : jan 10, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "Battery.h"

void blink_alert(void* arg) {
	gpio_set_level(PWR_LED_GPIO, 0);
	vTaskDelay(200 / portTICK_PERIOD_MS);
	gpio_set_level(PWR_LED_GPIO, 1);
	vTaskDelay(200 / portTICK_PERIOD_MS);
}

uint8_t Battery::read_batteryLevel() {
	int average = 0;
	for (int i = 0; i < 10; i++) {
		int measure = adc1_get_raw(ADC_CHANNEL);
		average += measure;
	}
	average /= 10;

	int result = map_battery(average, 2550, 3500, 0, 100);
	if (result > 100)
		result = 100;
	if (result < 0)
		result = 0;
	if (result < 40) {
		for (int i = 0; i < 4; i++) {
				gpio_set_level(PWR_LED_GPIO, 0);
				vTaskDelay(200 / portTICK_PERIOD_MS);
				gpio_set_level(PWR_LED_GPIO, 1);
				vTaskDelay(200 / portTICK_PERIOD_MS);
			}
	}
	return result;
}

