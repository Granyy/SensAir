#ifndef MAP_HPP
#define MAP_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <ostream>
#include "coordinates.hpp"
#include "datapoint.hpp"

class Map {
	using Bucket = std::vector<Datapoint>;

public:
	Map(const std::string& filename);

	void add(const Datapoint& datapoint);
	auto getWithin(const Coordinates& coordinates, double radius) -> std::vector<Datapoint>;

	void save(const std::string& filename);

private:
	double bucketSize;
	std::unordered_map<Coordinates, Bucket, Coordinates::Hash, Coordinates::EqualTo> buckets;

	auto bucketCoordinates(const Coordinates& coordinates) -> Coordinates;

	friend auto operator<<(std::ostream& os, const Map& map) -> std::ostream&;
};



#endif // MAP_HPP
