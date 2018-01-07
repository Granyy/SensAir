#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include "server.hpp"

int main(int argc, char *argv[]) {
	int port = 8080;
	if (argc == 2) {
		port = std::strtol(argv[1], NULL, 0);
	}

	Server server(port);
	std::cout << "Listening on port " << port << std::endl;

	auto inputHandler = []() {
		std::string input;
		std::cin >> input;
		return input;
	};

	std::string input;
	auto future = std::async(std::launch::async, inputHandler);
	do {
		input.clear();
		if (future.wait_for(std::chrono::milliseconds(10)) == std::future_status::ready) {
			input = future.get();
			if (input != "q") {
				future = std::async(std::launch::async, inputHandler);
			}
		}

		if (input == "p") {
			server.printMap();
		} else if (input == "s") {
			server.saveMap();
		}
	} while (input != "q");
}
