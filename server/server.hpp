#ifndef SERVER_HPP
#define SERVER_HPP

#include <pistache/endpoint.h>
#include <vector>
#include <string>
#include <optional>
#include "map.hpp"
#include "datapoint.hpp"

using namespace Pistache;

class Server : Http::Endpoint {
public:
	Server(int port);
	~Server();

	void printMap();
	void saveMap();

private:
	Map map;
	
	auto handleGet(const std::string& latitudeString, const std::string& longitudeString, const std::string& radiusString) -> std::string;
	bool handlePost(const std::string& request);

	static auto payloadFromDatapoints(std::vector<Datapoint> datapoints) -> std::string;
	static auto datapointsFromPayload(const std::string& payload) -> std::optional<std::vector<Datapoint>>;

	friend class HttpHandler;
};

#endif // SERVER_HPP
