#include <iostream>
#include "Udp_server.hpp"
#include <boost/asio.hpp>
#include <string>

//3 параметра : порт, который слушаем, ip/hostname кому слать, dest-port

int main() {
	/*try {
		boost::asio::io_service io_service;
		Udp_server server(io_service);
		io_service.run();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}*/

	boost::asio::io_service io_service;
	Udp_server server(io_service, "8.8.8.8", "1337");

	server.send("Hi!");

    return EXIT_SUCCESS;
}

