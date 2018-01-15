/******************************************************************************/
/*        @TITLE : GasTreatment.cpp                                           */
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
	error = false;
	read_gas();
	if ((CO > CO_LIMIT_LOW)&(CO<CO_LIMIT_HIGH)) {
		buzzer.beep();
	}
	gasRawValue = {CO, CO2, NO2, VOC};
	gasValue.CO=map_gas(CO, 1, 8, 0, 100);
	if ((gasRawValue.CO == -1)|(gasValue.CO > 100)) {
		gasValue.CO = 0;
		error = true;
	}
	gasValue.CO2=map_gas(CO2, 400, 1000, 0, 100);
	if ((gasRawValue.CO2 == -1)|(gasValue.CO2 > 100)) {
		gasValue.CO2 = 0;
		error = true;
	}
	gasValue.NO2=map_gas(NO2,0.10,0.30,0,100);
	if ((gasRawValue.NO2 == -1)|(gasValue.NO2 > 100)) {
		gasValue.NO2 = 0;
		error = true;
	}
	gasValue.VOC=map_gas(VOC,0,600,0,100);
	if ((gasRawValue.VOC == -1)|(gasValue.VOC > 100)) {
		gasValue.VOC = 0;
		error = true;
	}
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

bool GasTreatment::get_status() {
	return error;
}

