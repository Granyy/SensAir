#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <ostream>

struct Coordinates {
	double latitude;
	double longitude;

	struct Hash;
	struct EqualTo;
};

struct Coordinates::Hash {
    auto operator()(const Coordinates& coordinates) const -> std::size_t;
};

struct Coordinates::EqualTo {
	bool operator()(const Coordinates& lhs, const Coordinates& rhs) const;
};

auto distance(const Coordinates& lhs, const Coordinates& rhs) -> double;
auto operator<<(std::ostream& os, const Coordinates& coordinates) -> std::ostream&;

#endif // COORDINATES_HPP
