/******************************************************************************/
/*        @TITLE : Battery.h                                                  */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : jan 10, 2017                                               */
/* @MODIFICATION : jan 10, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/


#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "Configuration.h"
#include "driver/adc.h"
#include <iostream>

#define map_battery(x, in_min, in_max, out_min, out_max) ((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min)

using namespace std;

class Battery {
private:
	uint8_t batteryLevel = 0;
public:
	uint8_t read_batteryLevel();
};
  

#endif
