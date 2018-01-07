#include "httphandler.hpp"
#include <memory>

using namespace Pistache;

HttpHandler::HttpHandler(Server* server)
: server(server) {
}

void HttpHandler::onRequest(const Http::Request& request, Http::ResponseWriter response) {
	if (request.resource() == "/") {
		if (request.method() == Http::Method::Post) {
			if (server->handlePost(request.body())) {
				response.send(Http::Code::Ok);
			} else {
				std::cout << "Error parsing POST request:\n" << request.body() << std::endl;
				response.send(Http::Code::Bad_Request);
			}
		} else if (request.method() == Http::Method::Get) {
			auto latitude = request.query().get("lat");
			auto longitude = request.query().get("long");
			auto radius = request.query().get("radius");

			if (latitude.isEmpty() || longitude.isEmpty() || radius.isEmpty()) {
				std::cout << "Error parsing GET request:\n" << request.body() << std::endl;
				response.send(Http::Code::Bad_Request);
			} else {
				auto payload = server->handleGet(latitude.get(), longitude.get(), radius.get());
				response.send(Http::Code::Ok, payload, MIME(Text, Plain));
			}
		} else {
			response.send(Http::Code::Method_Not_Allowed);
		}
	} else {
		response.send(Http::Code::Not_Found);
	}
}

auto HttpHandler::clone() const -> std::shared_ptr<Tcp::Handler> {
	return std::make_shared<HttpHandler>(server);
}