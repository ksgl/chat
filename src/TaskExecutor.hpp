#pragma once

#include <iostream>

#include "json.hpp"
#include "UDPServer.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include <string>
#include <map>
#include <functional>


struct Link {
    boost::asio::ip::udp::endpoint local;
    boost::asio::ip::udp::endpoint remote;
};

class TaskExecutor : public MessageHandlerBase {
public:
    typedef std::function<void(const nlohmann::json&)> Callback;
    
    void execute_async(const nlohmann::json& j, const Callback& callback) {
        ios.post([this, j, callback](){ this->execute(j, callback); }); // enqueue task
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
        command_callbacks[id](msg.payload);
        
        // remember endpoint from user
        // tipa messeg
        // ot kogo
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
    
    /*
    id : 1
    command : hello;
    payload : {...}
    
    id : 1
    answer : fail
    payload : {
        reason : unknown command
    }
    */

    
};
