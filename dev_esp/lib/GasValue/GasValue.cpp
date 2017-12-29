/******************************************************************************/
/*        @TITLE : GasValue.cpp                                               */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "GasValue.h"



GasValue::GasValue() {
	gasSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(gasSemaphore);
	gasValue.CO = 0;
	gasValue.CO2 = 0;
	gasValue.NO2 = 0;
	gasValue.VOC = 0;
	gasRawValue.CO = 0;
	gasRawValue.CO2 = 0;
	gasRawValue.NO2 = 0;
	gasRawValue.VOC = 0;
}

struct gasRaw GasValue::get_gasRawValue() {
	struct gasRaw _gasRawValue;
	if(xSemaphoreTake(gasSemaphore,portMAX_DELAY) == pdTRUE) {
		_gasRawValue = gasRawValue;
		xSemaphoreGive(gasSemaphore);
	}
	return _gasRawValue;

}

struct gas GasValue::get_gasValue() {
	struct gas _gasValue;
	if(xSemaphoreTake(gasSemaphore,portMAX_DELAY) == pdTRUE) {
		_gasValue = gasValue;
		xSemaphoreGive(gasSemaphore);
	}
	return _gasValue;
}
void GasValue::set_gasValue(struct gas _gasValue) {
	if(xSemaphoreTake(gasSemaphore,portMAX_DELAY) == pdTRUE) {
		gasValue = _gasValue;
		xSemaphoreGive(gasSemaphore);
	}
}
void GasValue::set_gasRawValue(struct gasRaw _gasRawValue) {
	if(xSemaphoreTake(gasSemaphore,portMAX_DELAY) == pdTRUE) {
		gasRawValue = _gasRawValue;
		xSemaphoreGive(gasSemaphore);
	}

}