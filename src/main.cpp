#include "TaskExecutor.hpp"

#include <boost/asio.hpp>

#include <csignal>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>


namespace util {
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
    
    // trim from start (copying)
    static inline std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
    }
    
    // trim from end (copying)
    static inline std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
    }
    
    // trim from both ends (copying)
    static inline std::string trim_copy(std::string s) {
        trim(s);
        return s;
    }
}

class CLI {
public:
    explicit CLI(boost::asio::io_service& io_service)
        : ios(io_service)
        , tex(io_service)
    {
        tex.start();
        ios.post(boost::bind(&CLI::read_line, boost::ref(*this)));
    }
    
private:
    static void read_line(CLI& cli) {
        std::string cmd;
        std::getline(std::cin, cmd);
        util::trim(cmd);
        if (cli.execute_line(cmd)) {
            cli.ios.post(boost::bind(&CLI::read_line, boost::ref(cli)));
        }
        else {
            std::cout << "Exiting..." << std::endl;
            cli.tex.stop();
        }
    }
    
    bool execute_line(const std::string& str) {
        if (str.empty()) {
            return false;
        }
        
        auto cmd = nlohmann::json::parse(str);
        tex.execute_async(cmd, [this](const nlohmann::json& res){ this->process_result(res); });
        return true;
    }
    
    void process_result(const nlohmann::json& res) {
        std::cout << res.dump() << std::endl;
    }
    
private:
    boost::asio::io_service& ios;
    TaskExecutor tex;
};

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
        
        boost::asio::io_service io_service;
        CLI cli(io_service);
        
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

void task_execution() {
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
        
        boost::asio::io_service io_service;
        CLI cli(io_service);
        
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
}



