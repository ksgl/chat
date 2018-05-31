#pragma once

#include <iostream>

#include "json.hpp"
#include "UDPServer.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <map>
#include <functional>
#include <thread>
#include <mutex>
#include <exception>


struct Link {
    boost::asio::ip::udp::endpoint local;
    boost::asio::ip::udp::endpoint remote;
};

// Class TaskExecutor provides a functionality to enqueue and execute tasks from GUI application.
class TaskExecutor : public MessageHandlerBase {
public:
    typedef std::function<void(const nlohmann::json&)> Callback; // generic Callback function type to be called after recieving a response from TaskExecutor (response is given in nlohmann::json)
    
    // this function submits a task (nlohamann::json) coming from GUI to task queue (boost::asio::io_service internal queue), as soon as it is possible it is executed and callback is called on the response (which is, as stated above, is too an nlohmann::json), thread-safe
    void execute_async(const nlohmann::json& j, const Callback& callback) {
        ios.post([this, j, callback](){ this->execute(j, callback); });
    }
    
    // constructor instanciates a UDPServer instance (from UDPServer.hpp), sets a message handler (the function, that will be called as soon as we receive something on the socket), registers a specific io_service that will be busy with this particular task of receiving messages from GUI and calling callback on the response
    explicit TaskExecutor(boost::asio::io_service& io_service)
        : ios(io_service)
        , serv(io_service)
    {
        serv.set_message_handler(this);
    }
    
    virtual ~TaskExecutor() {
        stop();
    }
    
    virtual void handle(const Message& msg) override {
        try {
            if (msg.payload.find("id") != msg.payload.end() && msg.payload["id"].is_string()) {
                auto id = msg.payload["id"].get<std::string>();
                Message passable = msg;
                passable.payload.erase("id");
                
                if (command_callbacks.count(id) != 0) {
                    command_callbacks[id](passable.payload);
                    command_callbacks.erase(id);
                }
                else {
                    std::cout << "Fail to execute: no callback registered";
                }
            }
            else {
                if (oclb) {
                    oclb(msg.payload);
                    std::cout << "Worked, received: " << msg.payload.dump();
                }
                else {
                    std::cout << "Fail to process this message: no orphan callback registered" << std::endl;
                }
            }
        }
        catch (std::exception ex) {
            std::cout << "Fail to receive message from server/endpoint: " << ex.what() << std::endl;
        }
    }
    
    void set_orphan_message_callback(const Callback& callback) {
        oclb = callback;
    }
    
    // starting the UDPServer
    void start() {
        serv.start();
    }
    
    // stoping the UDPServer
    void stop() {
        serv.stop();
    }
    
private:
    
    const boost::asio::ip::udp::endpoint server_endpoint{boost::asio::ip::address::from_string("91.211.107.158"), 1337}; //the enpoint (an ip and port pair) of our global PseudoNS
    boost::asio::io_service& ios;
    UDPServer serv;
    std::map<std::string, Link> user_links; // tree of user_nicknames<->ip addresses to implement peer2peer logic
    std::map<std::string, Callback> command_callbacks; // map of command<->callback, to be used in handle and execute
    Callback oclb = [](nlohmann::json j){}; // all our messages with the server are provided with a unique id from our side; this is an orphan callback, which used in case of receiving nlohmann::json without any unique id (this means that somebody has sent us something, it is not a response from server or any kind of service messaging). This callback is extremely important to be initialized, because it is absolutely common sense to be expecting a message from anyone on the socket. Initially it is set to do nothing
    
    std::mutex mt;
    
    void execute(const nlohmann::json& j, const Callback& callback) {
        auto cmd = j; // received command (all command json types can be found in service_messages.md)
        
        // generating a unique id and adding it to the command json
        boost::uuids::uuid unique_id = boost::uuids::random_generator()();
        std::string id = boost::lexical_cast<std::string>(unique_id);
        cmd["payload"]["id"] = id;
        
        // user.register
        // checking if the requested field exists and is a string (validation and sanity checks) then we proceed with building the command<->callback tree and sending the command to the server where it will be processed accordingly to the requested task
        if (cmd.find("command") != cmd.end() && cmd["command"].is_string() && cmd["command"].get<std::string>() == "user.register") {
            command_callbacks[id] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            msg.to = server_endpoint;
            msg.payload = cmd;
            serv.send(msg);
        }
        
        // user.login
        // checking if the requested field exists and is a string (validation and sanity checks) then we proceed with building the command<->callback tree and sending the command to the server where it will be processed accordingly to the requested task
        else if (cmd.find("command") != cmd.end() && cmd["command"].is_string() && cmd["command"].get<std::string>() == "user.login") {
            command_callbacks[id] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            msg.to = server_endpoint;
            msg.payload = cmd;
            serv.send(msg);
        }
        
        // user.add_friend
        // checking if the requested field exists and is a string (validation and sanity checks) then we proceed with building the command<->callback tree and sending the command to the server where it will be processed accordingly to the requested task
        else if (cmd.find("command") != cmd.end() && cmd["command"].is_string() && cmd["command"].get<std::string>() == "user.add_friend") {
            command_callbacks[id] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            msg.to = server_endpoint;
            msg.payload = cmd;
            serv.send(msg);
        }
        
        // user.message_send
        // checking if the requested field exists and is a string (validation and sanity checks) then we proceed with building the command<->callback tree and sending the message to the remote endpoint, which we form from the information we have from GUI json
        else if (cmd.find("command") != cmd.end() && cmd["command"].is_string() && cmd["command"].get<std::string>() == "message.send") {
            command_callbacks[id] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            boost::asio::ip::udp::endpoint to_endpoint{boost::asio::ip::address::from_string(cmd["payload"]["message"]["to_ip"]), 8080};
            msg.to = to_endpoint;
            msg.payload = cmd;
            serv.send(msg);
        }
        
        else {
            // in case of invalid json
            nlohmann::json res;
            res["answer"] = "fail";
            res["payload"]["id"] = cmd["payload"]["id"];
            res["payload"]["reason"] = "unknown command";
            callback(res);
        }
    }
};

// TaskExecutor in a thread to be able to run with GUI thread 
class TaskExecuterRunner {
public:
    TaskExecuterRunner()
    : task_executor_(io_service_)
    {
    }
    
    ~TaskExecuterRunner() {
        stop();
        
        auto ex = pop_exception();
        if (ex) {
            try {
                std::rethrow_exception(ex);
            }
            catch (const std::exception& ex) {
                std::printf("Task executor exception: %s", ex.what());
            }
            catch (...) {
                std::printf("Task executor exception: <unknown>");
            }
        }
    }
    
    void set_orphan_message_callback(const TaskExecutor::Callback& callback) {
        io_service_.post([this, callback](){ this->task_executor_.set_orphan_message_callback(callback); });
    }
    
    void execute_async(const nlohmann::json& j, const TaskExecutor::Callback& callback) {
        if (!is_running()) {
            throw std::runtime_error("task executor is not running");
        }
        
        task_executor_.execute_async(j, callback);
    }
    
    void start() {
        if (is_running()) {
            throw std::runtime_error("task executor is already running");
        }
        
        io_service_.post([this](){ this->task_executor_.start(); });
        thread_ = std::thread([this](){ this->run(); });
    }
    
    void stop() {
        if (is_running()) {
            io_service_.post([this](){ this->task_executor_.stop(); });
        }
        
        if (thread_.joinable()) {
            thread_.join();
        }
        
        thread_ = std::thread();
        running_ = false;
    }
    
    bool is_running() const {
        return running_;
    }
    
    std::exception_ptr pop_exception() {
        if (is_running()) {
            throw std::runtime_error("task executor is still running");
        }
        
        auto ex = ex_;
        ex_ = std::exception_ptr{};
        
        return ex;
    }
    
private:
    void run() {
        running_ = true;
        ex_ = std::exception_ptr{};
        
        try {
            io_service_.run();
        } catch (...) {
            ex_ = std::current_exception();
        }
        
        running_ = false;
    }
    
private:
    std::thread thread_;
    std::atomic<bool> running_;
    std::exception_ptr ex_;
    boost::asio::io_service io_service_;
    TaskExecutor task_executor_;
};
