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

class TaskExecutor : public MessageHandlerBase {
public:
    typedef std::function<void(const nlohmann::json&)> Callback;
    
    void execute_async(const nlohmann::json& j, const Callback& callback) {
        ios.post([this, j, callback](){ this->execute(j, callback); }); // enqueue task, thread-safe
    }
    
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
          //  std::cout << "Received text: " << msg.payload.dump();
            
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
                if (oclb != nullptr) {
                    oclb(msg.payload);
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
    
    void start() {
        serv.start();
    }
    
    void stop() {
        serv.stop();
    }
    
private:
    
    const boost::asio::ip::udp::endpoint server_endpoint{boost::asio::ip::address::from_string("91.211.107.158"), 1337};
    boost::asio::io_service& ios;
    UDPServer serv;
    std::map<std::string, Link> user_links;
    std::map<std::string, Callback> command_callbacks;
    Callback oclb = [](const nlohmann::json&){};
    
    std::mutex mt;
    
    void execute(const nlohmann::json& j, const Callback& callback) {
        auto cmd = j;
        
        boost::uuids::uuid unique_id = boost::uuids::random_generator()();
        std::string id = boost::lexical_cast<std::string>(unique_id);
        cmd["payload"]["id"] = id;
        
        //std::cout << cmd.dump();
        
        // user.register
        if (cmd.find("command") != cmd.end() && cmd["command"].is_string() && cmd["command"].get<std::string>() == "user.register") {
            command_callbacks[id] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            msg.to = server_endpoint;
            msg.payload = cmd;
            serv.send(msg);
        }
        
        // user.login
        else if (cmd.find("command") != cmd.end() && cmd["command"].is_string() && cmd["command"].get<std::string>() == "user.login") {
            command_callbacks[id] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            msg.to = server_endpoint;
            msg.payload = cmd;
            serv.send(msg);
        }
        
        // user.add_friend
        else if (cmd.find("command") != cmd.end() && cmd["command"].is_string() && cmd["command"].get<std::string>() == "user.add_friend") {
            command_callbacks[id] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            msg.to = server_endpoint;
            msg.payload = cmd;
            serv.send(msg);
        }
        
        // user.message_send
        else if (cmd.find("command") != cmd.end() && cmd["command"].is_string() && cmd["command"].get<std::string>() == "message.send") {
            command_callbacks[id] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            boost::asio::ip::udp::endpoint to_endpoint{boost::asio::ip::address::from_string(cmd["payload"]["message"]["to_ip"]), 8080};
            msg.to = to_endpoint;
            msg.payload = cmd["payload"]["message"]["text"];
            serv.send(msg);
        }
        
        else {
            nlohmann::json res;
            res["answer"] = "fail";
            res["payload"]["id"] = cmd["payload"]["id"];
            res["payload"]["reason"] = "unknown command";
            callback(res);
        }
    }
};

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
