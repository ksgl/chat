#include <chat/JSONTaskExecutor.hpp>
#include <chat/UDPRPCServer.hpp>

#include <nlohmann/json.hpp>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <locale>
#include <stdexcept>
#include <string>

#include <csignal>
#include <cstdio>
#include <cstdlib>


extern "C" {

    void handle_critical_signal(int signal) {
        std::fprintf(stderr, "\nImmediate shutdown on signal: %d (CRITICAL)\n", signal);
        // Exitting with code that incorporates the signal (128 + n), according to the convention described here: http://tldp.org/LDP/abs/html/exitcodes.html
        const int base = 128;
        // Use std::exit() instead of std::_Exit() to enable executing the rest "cleanup" code which is run after the exit(). Required when valgrind'ing.
        std::_Exit(base + signal);
//      std::exit(base + signal);
    }

} // extern "C"

namespace util {

    inline void install_critical_signal_handler() {
        struct ::sigaction signal_handler;
        std::memset(&signal_handler, 0, sizeof(signal_handler));
        signal_handler.sa_handler = handle_critical_signal;
//      ::sigaction(SIGBUS,  &signal_handler, nullptr);
        ::sigaction(SIGILL,  &signal_handler, nullptr);
        ::sigaction(SIGABRT, &signal_handler, nullptr);
        ::sigaction(SIGFPE,  &signal_handler, nullptr);
        ::sigaction(SIGSEGV, &signal_handler, nullptr);
    }

    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }
    
    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }
    
    // trim from both ends (in place)
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

} // namespace util

// Simple CLI to test. Takes a string (compact json) from stdin, executes it (we assume that this particular json is one of service_messages.md). Received/resulting messages are just printed to stdout.
class CLI {
public:
    CLI(const nlohmann::json& config_json, boost::asio::io_service& io_service)
        : io_service_(io_service)
        , rpc_server_(chat::implementation::UDPRPCServer::Params(config_json), io_service)
        , task_executor_(chat::implementation::JSONTaskExecutor::Params(config_json), io_service)
    {
        task_executor_.set_orphan_message_callback([this](const std::string& command){ this->process_orphan(command); });
        task_executor_.set_rpc_server(&rpc_server_);
        task_executor_.start();
        io_service_.post(boost::bind(&CLI::read_line, boost::ref(*this)));
    }
    
private:
    static void read_line(CLI& cli) {
        std::string cmd;
        std::getline(std::cin, cmd);
        util::trim(cmd);

        if (cli.execute_line(cmd)) {
            cli.io_service_.post(boost::bind(&CLI::read_line, boost::ref(cli)));
        }
        else {
            std::cout << "Exiting..." << std::endl;
            cli.task_executor_.stop();
        }
    }
    
    bool execute_line(const std::string& command) {
        if (command == "exit") {
            return false;
        }

        if (!command.empty()) {
            try {
                task_executor_.execute_async(command, [this](const std::string& command){ this->process_result(command); });
            }
            catch (const std::exception& ex) {
                std::cout << "Failed to execute the command: " << ex.what() << std::endl;
            }
        }

        return true;
    }

    void process_orphan(const std::string& command) {
        auto command_json = nlohmann::json::parse(command); // ...parse to check the syntax.
        std::cout << "Received a command without an id: " << command_json.dump() << std::endl;
    }

    void process_result(const std::string& command) {
        auto command_json = nlohmann::json::parse(command); // ...parse to check the syntax.
        std::cout << "Received a command: " << command_json.dump() << std::endl;
    }

private:
    boost::asio::io_service& io_service_;
    chat::implementation::UDPRPCServer rpc_server_;
    chat::implementation::JSONTaskExecutor task_executor_;
};


int main(int argc, const char* argv[]) {
    int exit_code = EXIT_SUCCESS;
    
    try {
        util::install_critical_signal_handler();

        if (argc > 2) {
            throw std::runtime_error("usage: " + std::string(argv[0]) + " [config-json-file]");
        }

        nlohmann::json config_json;

        if (argc == 2) {
            const std::string config_file = argv[1];
            if (!boost::filesystem::exists(config_file)) {
                throw std::runtime_error("config file " + config_file + " does not exist");
            }
            std::ifstream ifs(config_file);
            config_json = nlohmann::json::parse(ifs);
        }

        boost::asio::io_service io_service;
        CLI cli(config_json, io_service);
        io_service.run();
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

