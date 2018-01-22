#include "datapoint.hpp"

auto Datapoint::meanValue() -> double {
	return (value_CO + value_CO2 + value_NO2 + value_VOC) / 4;
}