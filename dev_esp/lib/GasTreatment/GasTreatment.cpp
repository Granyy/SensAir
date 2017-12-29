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
	gasRawValue.CO = CO;
	gasRawValue.CO2 = CO2;
	gasRawValue.NO2 = NO2;
	gasRawValue.VOC = VOC;
	gasValue.CO=map_gas(CO, 0, 80, 0, 100);
	gasValue.CO2=map_gas(CO2, 400, 500, 0, 100);
	gasValue.NO2=map_gas(NO2,0.10,0.20,0,100);
	gasValue.VOC=map_gas(VOC,0,1000,0,100);
	cout << "CO: "  << (int)gasValue.CO  << " | " << gasRawValue.CO  << endl;
	cout << "CO2: " << (int)gasValue.CO2 << " | " << gasRawValue.CO2 << endl;
	cout << "NO2: " << (int)gasValue.NO2 << " | " << gasRawValue.NO2 << endl;
	cout << "VOC: " << (int)gasValue.VOC << " | " << gasRawValue.VOC << endl;
}

struct gas GasTreatment::get_gasValue() {
	return gasValue;
}

struct gasRaw GasTreatment::get_gasRawValue() {
	return gasRawValue;
}
