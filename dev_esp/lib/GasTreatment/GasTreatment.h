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


using namespace std;


struct gas {
    uint8_t CO;
    uint8_t CO2;
    uint8_t VOC;
    uint8_t NO2;
};

class GasTreatment {
	private :
		GroveGasSensor groveGasSensor;
		MicsGasSensor micsGasSensor;
		float CO;
		float CO2;
		float VOC;
		float NO2;
		struct gas gasValue;

	public :
		void begin();
		void read_gas();
		void treat_gas();
		struct gas get_gasValue();
};


#endif