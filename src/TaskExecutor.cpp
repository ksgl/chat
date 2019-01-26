#include <chat/TaskExecutor.hpp>


namespace chat::interface {

    void TaskExecutor::set_orphan_message_callback(const Callback& callback) {
        orphan_message_callback_ = callback;
    }

    void TaskExecutor::set_rpc_server(RPCServer* server) {
        rpc_server_ = server;
        if (rpc_server_) {
            rpc_server_->set_message_handler(this);
            rpc_server_->start();
        }
    }

} // namespace chat::interface

