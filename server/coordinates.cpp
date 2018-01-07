#include "coordinates.hpp"
#include <functional>
#include <cmath>

auto Coordinates::Hash::operator()(const Coordinates& coordinates) const -> size_t {
    auto h1 = std::hash<double>()(coordinates.latitude);
    auto h2 = std::hash<double>()(coordinates.longitude);
    return h1 ^ (h2 << 1);
}

bool Coordinates::EqualTo::operator()(const Coordinates& lhs, const Coordinates& rhs) const {
	return (lhs.latitude == rhs.latitude) && (lhs.longitude == rhs.longitude);
}

auto distance(const Coordinates& lhs, const Coordinates& rhs) -> double {
	return std::hypot(rhs.latitude - lhs.latitude, rhs.longitude - lhs.longitude);
}

auto operator<<(std::ostream& os, const Coordinates& coordinates) -> std::ostream& {
	os << coordinates.latitude << ";" << coordinates.longitude;
	return os;
}