/******************************************************************************/
/*        @TITLE : GasTreatment.cpp                                            */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "GasTreatment.h"

void GasTreatment::begin() {
	groveGasSensor.power_on();
}

void GasTreatment::read_gas() {
	CO = groveGasSensor.measure_CO();
	NO2 = groveGasSensor.measure_NO2();

	micsGasSensor.read_sensor();
	CO2 = micsGasSensor.get_CO2();
	VOC = micsGasSensor.get_VOC();
}

void GasTreatment::treat_gas() {
	read_gas();
	cout << "Some treatment" << endl;
}

struct gas GasTreatment::get_gasValue() {
	return gasValue;
}