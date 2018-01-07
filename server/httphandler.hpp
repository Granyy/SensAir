#ifndef HTTPHANDLER_HPP
#define HTTPHANDLER_HPP

#include "server.hpp"

class HttpHandler : public Http::Handler {
public:
	using tag = Http::details::prototype_tag;

	HttpHandler(Server* server);
	void onRequest(const Http::Request& request, Http::ResponseWriter response);
	auto clone() const -> std::shared_ptr<Tcp::Handler>;

private:
	Server* server;
};

#endif // HTTPHANDLER_HPP
