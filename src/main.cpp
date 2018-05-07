#include "UDPServer.hpp"

#include <boost/asio.hpp>

#include <csignal>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <stdexcept>


extern "C" {
    
    void handle_critical_signal(int signal) {
        std::fprintf(stderr, "\nImmediate shutdown on signal: %d (CRITICAL)\n", signal);
        std::_Exit(128 + signal);
//      std::exit(128 + signal);
    }
    
} // extern "C"

int main(int argc, const char* argv[]) {
    int exit_code = EXIT_SUCCESS;
    
    try {
        // Installing the critical signal handler.
        struct ::sigaction signal_handler;
        std::memset(&signal_handler, 0, sizeof(signal_handler));
        signal_handler.sa_handler = handle_critical_signal;
//      ::sigaction(SIGBUS,  &signal_handler, nullptr);
        ::sigaction(SIGILL,  &signal_handler, nullptr);
        ::sigaction(SIGABRT, &signal_handler, nullptr);
        ::sigaction(SIGFPE,  &signal_handler, nullptr);
        ::sigaction(SIGSEGV, &signal_handler, nullptr);

        MyMessageHandler my_message_handler;
        boost::asio::io_service io_service;
        UDPServer server(io_service);
        
        server.set_message_handler(&my_message_handler);
        server.start();
        
        // TODO: here, submit some tasks that will (directly or indirectly) call server.send(message);
        
        io_service.run();
        server.stop();
        
        // TODO: server.stop() may schedule some more tasks on io_service??
        
        // TODO: on throw, server.stop() is not called, and there will be some scheduled tasks on io_service!
        
    }
    // Use fprintf here to avoid riscs of new uncaught exceptions.
    catch (const std::exception& ex) {
        std::fprintf(stderr, "\nError: %s\n", ex.what());
        exit_code = EXIT_FAILURE;
    }
    catch (...) {
        std::fprintf(stderr, "\nError: unknown\n");
        exit_code = EXIT_FAILURE;
    }
    
    return exit_code;
}
