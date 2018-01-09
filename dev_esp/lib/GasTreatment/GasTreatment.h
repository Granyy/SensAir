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
#include "GasValue.h"
#include "Buzzer.h"

#define map_gas(x, in_min, in_max, out_min, out_max) ((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min)
#define CO_LIMIT 50

using namespace std;


class GasTreatment {
	private :
		GroveGasSensor groveGasSensor;
		MicsGasSensor micsGasSensor;
		Buzzer buzzer;
		float CO = -1;
		float CO2 = -1;
		float VOC = -1;
		float NO2 = -1;
		struct gas gasValue = {0,0,0,0};
		struct gasRaw gasRawValue = {0,0,0,0};

	public :
		void begin();
		void read_gas();
		void treat_gas();
		struct gas get_gasValue();
		struct gasRaw get_gasRawValue();
};


#endif
