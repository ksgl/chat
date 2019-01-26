#pragma once

#include <memory>
#include <string>


namespace chat::interface {

    class RPCServer {
    public:
        class Endpoint {
        public:
            virtual ~Endpoint() = default;
            virtual void from_string(const std::string& str) = 0;
            virtual std::string to_string() const = 0;
        };

        class Message {
        public:
            virtual ~Message() = default;
            virtual Endpoint& from() = 0;
            virtual Endpoint& to() = 0;
            virtual const std::string& payload() const = 0;
            virtual void payload(const std::string& str) = 0;
        };

        class MessageHandler {
        public:
            virtual ~MessageHandler() = default;
            virtual void handle(const Message& message) = 0;
        };

        virtual ~RPCServer() = default;

        virtual void start() = 0;
        virtual void stop() = 0;

        virtual std::shared_ptr<Message> create_message() const = 0;
        virtual std::shared_ptr<Endpoint> get_local_endpoint() const = 0;

        virtual void send(const Message& message) = 0;

        void set_message_handler(MessageHandler* message_handler); // ...do not take ownership. nullptr is allowed.

    protected:
        void process_received(const Message& message);

    private:
        MessageHandler* message_handler_ = nullptr;
    };

} // namespace chat::interface

