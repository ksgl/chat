#pragma once

#include <chat/RPCServer.hpp>

#include <functional>
#include <map>
#include <string>


namespace chat::interface {

    // Class TaskExecutor provides an interface for enqueueing and executing tasks from GUI application.
    class TaskExecutor : public RPCServer::MessageHandler {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;

        // Generic callback function type to be called after recieving a response from TaskExecutor.
        typedef std::function<void(const std::string&)> Callback;

        // Submit a task to queue. When the task is executed, the callback will be called on the response. Should be thread-safe.
        virtual void execute_async(const std::string& command, const Callback& callback) = 0;

        void set_orphan_message_callback(const Callback& callback);
        void set_rpc_server(RPCServer* server); // ...do not take ownership. nullptr is allowed.

    protected:
        // All our messages with the server are provided with a unique id from our side; this is an orphan callback, which used in case of receiving a command without any unique id (this means that somebody has sent us something, it is not a response from server or any kind of service messaging). This callback is extremely important to be initialized, because it is absolutely common sense to be expecting a message from anyone on the socket. Initially it is set to do nothing.
        Callback orphan_message_callback_ = [](const std::string& command){ /* do nothing */ };
        RPCServer* rpc_server_ = nullptr;
    };

} // namespace chat::interface

