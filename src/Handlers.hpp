#pragma once

#include "json.hpp"

/*
{Register, {name, pswd}}

{
    "command": "user.register",
    "payload": {
        "name": "jkhgkjhg"
    }
}
 
 */
class MessageHandlerBase {
public:
    virtual ~MessageHandlerBase() = default;
    virtual void handle(const Message&) = 0;
};

class MyMessageHandler : public MessageHandlerBase {
public:
    virtual void handle(const Message& message) override {
        std::cout << "Received a message from " << message.from << " (for " << message.to << "): " << message.text << std::endl;

        switch () {
            case:
                break;
                
            default:
                break;
        }
    }
    
private:
    
    
};