#include "server.hpp"
#include "httphandler.hpp"
#include <iostream>
#include <sstream>
#include <memory>

Server::Server(int port)
: Http::Endpoint(Address(Ipv4::any(), port)), map("datapoints.txt") {
	init(Http::Endpoint::options().threads(1).flags(Tcp::Options::InstallSignalHandler | Tcp::Options::ReuseAddr));
	setHandler(std::make_shared<HttpHandler>(this));
	serveThreaded();
}

Server::~Server() {
	shutdown();
}

void Server::printMap() {
	std::cout << map;
}

void Server::saveMap() {
	map.save("datapoints2.txt");
}

auto Server::handleGet(const std::string& latitudeString, const std::string& longitudeString, const std::string& radiusString) -> std::string {
	auto coordinates = Coordinates { std::stod(latitudeString), std::stod(longitudeString) };
	auto radius = std::stod(radiusString);
	auto datapoints = map.getWithin(coordinates, radius);
	return payloadFromDatapoints(datapoints);
}

bool Server::handlePost(const std::string& request) {
	auto datapointsOpt = datapointsFromPayload(request);

	if (datapointsOpt) {
		for (auto& datapoint : *datapointsOpt) {
			map.add(datapoint);
		}
	} 

	return datapointsOpt.has_value();
}

auto Server::payloadFromDatapoints(std::vector<Datapoint> datapoints) -> std::string {
	std::ostringstream oss;
	oss << "[";
	bool comma = false;
	for (auto& datapoint : datapoints) {
		if (comma) {
			oss << ",";
		}

		oss << "\n{ \"lat\": " << datapoint.coordinates.latitude
			<< ", \"lon\": " << datapoint.coordinates.longitude
			<< ", \"int\": " << datapoint.value << " }";

		comma = true;
	}
	oss << "\n]";
	return oss.str();
}

auto Server::datapointsFromPayload(const std::string& payload) -> std::optional<std::vector<Datapoint>> {
	auto datapoints = std::vector<Datapoint>();
	std::istringstream iss(payload);

	char c;
	iss >> c;
	if (iss.fail() || c != '[') {
		return {};
	}

	do {
		iss >> c;
		if (c == '{') {
			Datapoint datapoint;

			std::string str;
			iss >> str;
			if (iss.fail() || str != "\"lat\":") {
				return {};
			}

			iss >> datapoint.coordinates.latitude;

			iss >> c >> str;
			if (iss.fail() || c != ',' || str != "\"lon\":") {
				return {};
			}

			iss >> datapoint.coordinates.longitude;

			iss >> c >> str;
			if (iss.fail() || c != ',' || str != "\"int\":") {
				return {};
			}

			iss >> datapoint.value;

			iss >> c;
			if (iss.fail() || c != '}') {
				return {};
			}

			datapoints.push_back(datapoint);
		}

		iss >> c;
		if (iss.fail() || (c != ',' && c != ']')) {
			return {};
		}
	} while (!iss.fail() && c != ']');

	return datapoints;
}
