/******************************************************************************/
/*        @TITLE : BatteryValue.h                                             */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : jan 10, 2017                                               */
/* @MODIFICATION : jan 10, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "BatteryValue.h"



BatteryValue::BatteryValue() {
	batterySemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(batterySemaphore);
	batteryLevel = 0;
}

uint8_t BatteryValue::get_batteryLevel() {
	uint8_t _batteryLevel = 0;
	if(xSemaphoreTake(batterySemaphore,portMAX_DELAY) == pdTRUE) {
		_batteryLevel = batteryLevel;
		xSemaphoreGive(batterySemaphore);
	}
	return _batteryLevel;
}

void BatteryValue::set_batteryLevel(uint8_t _batteryLevel) {
	if(xSemaphoreTake(batterySemaphore,portMAX_DELAY) == pdTRUE) {
		batteryLevel = _batteryLevel;
		xSemaphoreGive(batterySemaphore);
	}
}