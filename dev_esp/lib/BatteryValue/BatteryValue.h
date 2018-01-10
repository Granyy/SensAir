/******************************************************************************/
/*        @TITLE : BatteryValue.h                                             */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : jan 10, 2017                                               */
/* @MODIFICATION : jan 10, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/


#ifndef __BATTERYVALUE_H__
#define __BATTERYVALUE_H__

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"


class BatteryValue {
private:
	uint8_t batteryLevel;
	SemaphoreHandle_t batterySemaphore = NULL;
public:
	BatteryValue();
	uint8_t get_batteryLevel();
	void set_batteryLevel(uint8_t _batteryLevel);
};


#endif
