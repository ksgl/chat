#pragma once

#include <iostream>

#include "json.hpp"
#include "UDPServer.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include <string>
#include <map>
#include <functional>
#include <thread>
#include <mutex>
#include <exception>

// id to generate
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

    virtual void handle(const Message& msg) {
        auto id = msg.payload["id"].get<std::string>();
        if (id no) {
            //create json
            oclb(js);
        }
        else {
            command_callbacks[id](msg.payload);
        }
        
        // remember endpoint from user
        // tipa messeg
        // ot kogo
        // create payload process into json
        // from to
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
    
    const boost::asio::ip::udp::endpoint server_endpoint{boost::asio::ip::address::from_string("1.1.1.1"), 1070};
    boost::asio::io_service& ios;
    UDPServer serv;
    std::map<std::string, Link> user_links; // соответствие чел <-> ip, ip of peer
    std::map<std::string, Callback> command_callbacks; // id <-> call CHECKS!
    Callback oclb = [](const nlohmann::json&){}; // пустая функция
    
    std::mutex mt;

    void execute(const nlohmann::json& j, const Callback& callback) {
        auto cmd = j;
        
        // user.register
        if(cmd["command"].get<std::string>() == "user.register") {
            command_callbacks[cmd["payload"]["id"].get<std::string>()] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            msg.to = server_endpoint;
            msg.payload = cmd["payload"];
            serv.send(msg);
        }

        // user.login
        else if (cmd["command"].get<std::string>() == "user.login") {
            command_callbacks[cmd["payload"]["id"].get<std::string>()] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            msg.to = server_endpoint;
            msg.payload = cmd["payload"];
            serv.send(msg);
        }

        // user.add_friend
        else if (cmd["command"].get<std::string>() == "user.add_friend") {
            command_callbacks[cmd["payload"]["id"].get<std::string>()] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint();
            msg.to = server_endpoint;
            msg.payload = cmd["payload"];
            serv.send(msg);
        }

         // user.message_send
        else if (cmd["command"].get<std::string>() == "message.send") {
            command_callbacks[cmd["payload"]["id"].get<std::string>()] = callback;
            Message msg;
            msg.from = serv.get_default_local_endpoint(); 
            //msg.to = // map
            
            msg.payload = cmd["payload"];
            serv.send(msg);
        }

        else {
            nlohmann::json res;
            res["id"] = cmd["id"];
            res["answer"] = "fail";
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
