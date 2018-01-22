#include "map.hpp"
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>
#include <algorithm>

#include <iostream>

Map::Map(const std::string& filename)
: bucketSize(0.005) {
	std::ifstream file(filename);
	for (std::string line; std::getline(file, line); ) {
		if (!std::all_of(line.begin(), line.end(), [](char c) -> bool { return std::isspace(c); } )) {
			std::stringstream s(line);
			if (line.substr(0, 11) == "bucketSize=") {
				s.ignore(11);
				s >> bucketSize;
			} else {
				Datapoint dp;
				char c1, c2, c3, c4, c5;
				s >> dp.coordinates.latitude >> c1 >> dp.coordinates.longitude >> c2
					>> dp.value_CO >> c3 >> dp.value_CO2 >> c4 >> dp.value_NO2 >> c5 >> dp.value_VOC;

				if (!s.fail() && c1 == ';' && c2 == ':' && c3 == ':' && c4 == ':' && c5 == ':') {
					add(dp);
				}
			}

			if (s.fail()) {
				throw std::runtime_error("Error parsing " + filename + " on: \"" + line + "\"");
			}
		}
	}
}

void Map::add(const Datapoint& datapoint) {
	buckets[bucketCoordinates(datapoint.coordinates)].push_back(datapoint);
}

auto Map::getWithin(const Coordinates& coordinates, double radius) -> std::vector<Datapoint> {
	auto datapoints = std::vector<Datapoint>();

	// add half the bucket size to include the last bucket
	auto maxLatitude = coordinates.latitude + radius + bucketSize/2.0;
	auto maxLongitude = coordinates.longitude + radius + bucketSize/2.0;

	for (auto latitude = coordinates.latitude - radius; latitude < maxLatitude; latitude += bucketSize) {
		for (auto longitude = coordinates.longitude - radius; longitude < maxLongitude + bucketSize/2.0; longitude += bucketSize) {
			auto bucket = buckets[bucketCoordinates({ latitude, longitude })];
			for (auto& datapoint : bucket) {
				if (distance(datapoint.coordinates, coordinates) <= radius) {
					datapoints.push_back(datapoint);
				}
			}
		}
	}

	return datapoints;
}

void Map::save(const std::string& filename) {
	std::ofstream file(filename);

	file << *this;
}

auto Map::bucketCoordinates(const Coordinates& coordinates) -> Coordinates {
	double latitude = std::floor(coordinates.latitude/bucketSize) * bucketSize;
	double longitude = std::floor(coordinates.longitude/bucketSize) * bucketSize;
	return {latitude, longitude};
}

auto operator<<(std::ostream& os, const Map& map) -> std::ostream& {
	os << "bucketSize=" << map.bucketSize << "\n\n";
	for (auto& bucket : map.buckets) {
		for (auto& datapoint : bucket.second) {
			os << datapoint.coordinates
				<< ":" << datapoint.value_CO
				<< ":" << datapoint.value_CO2
				<< ":" << datapoint.value_NO2
				<< ":" << datapoint.value_VOC << "\n";
		}
	}
	return os;
}