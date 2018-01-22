#ifndef DATAPOINT_HPP
#define DATAPOINT_HPP

#include "coordinates.hpp"

struct Datapoint {
	Coordinates coordinates;
	double value_CO;
	double value_CO2;
	double value_NO2;
	double value_VOC;

	auto meanValue() -> double;
};

#endif // DATAPOINT_HPP
