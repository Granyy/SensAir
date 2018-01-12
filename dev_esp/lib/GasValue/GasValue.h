/******************************************************************************/
/*        @TITLE : GasValue.h                                                 */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/


#ifndef __GASVALUE_H__
#define __GASVALUE_H__

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

struct gas {
    uint8_t CO;
    uint8_t CO2;
    uint8_t NO2;
    uint8_t VOC;
};

struct gasRaw {
    float CO;
    float CO2;
    float NO2;
    float VOC;
};

class GasValue {
private:
	struct gasRaw gasRawValue;
	struct gas gasValue;
	SemaphoreHandle_t gasSemaphore = NULL;
public:
	GasValue();
	struct gasRaw get_gasRawValue();
	struct gas get_gasValue();
	void set_gasValue(struct gas _gasValue);
	void set_gasRawValue(struct gasRaw _gasRawValue);

};


#endif
