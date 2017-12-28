/******************************************************************************/
/*        @TITLE : GasTreatment.h                                             */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/



#ifndef __GASTREATMENT_H__
#define __GASTREATMENT_H__

#include <string>
#include <iostream>
#include "GroveGasSensor.h"
#include "MicsGasSensor.h"

#define map_gas(x, in_min, in_max, out_min, out_max) ((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min)
#define GREEN_TH 20
#define YELLOW_TH 50
#define RED_TH 80


using namespace std;


struct gas {
    uint8_t CO;
    uint8_t CO2;
    uint8_t VOC;
    uint8_t NO2;
};

struct gasRaw {
    float CO;
    float CO2;
    float VOC;
    float NO2;
};

class GasTreatment {
	private :
		GroveGasSensor groveGasSensor;
		MicsGasSensor micsGasSensor;
		float CO = -1;
		float CO2 = -1;
		float VOC = -1;
		float NO2 = -1;
		struct gas gasValue;
		struct gasRaw gasRawValue;

	public :
		void begin();
		void read_gas();
		void treat_gas();
		struct gas get_gasValue();
		struct gasRaw get_gasRawValue();
};


#endif
