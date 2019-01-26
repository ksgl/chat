#include <chat/RPCServer.hpp>


namespace chat::interface {

    void RPCServer::set_message_handler(MessageHandler* message_handler) {
        message_handler_ = message_handler;
    }

    void RPCServer::process_received(const Message& message) {
        if (message_handler_) {
            message_handler_->handle(message);
        }
    }

} // namespace chat::interface

