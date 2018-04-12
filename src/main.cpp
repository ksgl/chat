#include <iostream>
#include "Udp_server.hpp"
#include <boost/asio.hpp>

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

	/*std::string msg;
	server.receive(msg);
	std::cout << "Your message: " << msg;
	
	io_service.run();
	*/

	server.send("Hi to Google from Ksusha");

    return EXIT_SUCCESS;
}

