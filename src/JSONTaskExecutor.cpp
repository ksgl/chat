#include <chat/JSONTaskExecutor.hpp>

#include <stdexcept>


namespace chat::implementation {

    JSONTaskExecutor::Params::Params(const nlohmann::json& config_json) {
        auto server_it = config_json.find("user_info_server");
        if (server_it != config_json.end()) {
            try {
                user_info_server = server_it->get<std::string>();
            }
            catch (const std::exception& ex) {
                throw std::runtime_error("unable to get user_info_server string value from config: " + std::string(ex.what()));
            }
        }
    }

    JSONTaskExecutor::JSONTaskExecutor(const Params& params, boost::asio::io_service& io_service)
        : params_(params)
        , io_service_(io_service)
    {
    }

    JSONTaskExecutor::~JSONTaskExecutor() {
        stop();
    }

    void JSONTaskExecutor::start() {
        stop();

        if (rpc_server_) {
            rpc_server_->start();
        }
    }

    void JSONTaskExecutor::stop() {
        if (rpc_server_) {
            rpc_server_->stop();
        }
    }

    void JSONTaskExecutor::handle(const interface::RPCServer::Message& message) {
        try {
            auto command = message.payload();
            auto command_json = nlohmann::json::parse(command);

            if (command_json.find("id") != command_json.end() && command_json["id"].is_string()) {
                auto id = command_json["id"].get<std::string>();
                command_json.erase("id");

                if (command_callbacks_.count(id) == 0) {
                    throw std::runtime_error("no callback registered for command id " + id);
                }

                command_callbacks_[id](command_json.dump());
                command_callbacks_.erase(id);
            }
            else {
                if (!orphan_message_callback_) {
                    throw std::runtime_error("no orphan callback registered (the command doesn't have an id)");
                }

                orphan_message_callback_(command);
            }
        }
        catch (const std::exception& ex) {
            std::cout << "Failed to process a message received from server/endpoint: " << ex.what() << std::endl;
        }
    }

    void JSONTaskExecutor::execute_async(const std::string& command, const Callback& callback) {
        auto command_json = nlohmann::json::parse(command);
        io_service_.post([this, command_json, callback](){ this->execute(command_json, callback); });
    }

    void JSONTaskExecutor::execute(nlohmann::json command_json, const Callback& callback) {
        // (all command json types can be found in service_messages.md)

        // Generating a unique id and adding it to the command json.
        boost::uuids::uuid unique_id = boost::uuids::random_generator()();
        std::string id = boost::lexical_cast<std::string>(unique_id);
        command_json["payload"]["id"] = id;

        // user.register
        // Checking if the requested field exists and is a string (validation and sanity checks) then we proceed with building the command<->callback tree and sending the command to the server where it will be processed accordingly to the requested task.
        if (command_json["command"].is_string() && command_json["command"].get<std::string>() == "user.register") {
            if (!rpc_server_) {
                throw std::runtime_error("RPC server is not set");
            }

            command_callbacks_[id] = callback;
            auto message_ptr = rpc_server_->create_message();
            auto& message = *message_ptr;

            message.from().from_string(rpc_server_->get_local_endpoint()->to_string());
            message.to().from_string(params_.user_info_server);
            message.payload(command_json.dump());

            rpc_server_->send(message);
        }

        // user.login
        // Checking if the requested field exists and is a string (validation and sanity checks) then we proceed with building the command<->callback tree and sending the command to the server where it will be processed accordingly to the requested task.
        else if (command_json["command"].is_string() && command_json["command"].get<std::string>() == "user.login") {
            if (!rpc_server_) {
                throw std::runtime_error("RPC server is not set");
            }

            command_callbacks_[id] = callback;
            auto message_ptr = rpc_server_->create_message();
            auto& message = *message_ptr;

            message.from().from_string(rpc_server_->get_local_endpoint()->to_string());
            message.to().from_string(params_.user_info_server);
            message.payload(command_json.dump());

            rpc_server_->send(message);
        }

        // user.add_friend
        // Checking if the requested field exists and is a string (validation and sanity checks) then we proceed with building the command<->callback tree and sending the command to the server where it will be processed accordingly to the requested task.
        else if (command_json["command"].is_string() && command_json["command"].get<std::string>() == "user.add_friend") {
            if (!rpc_server_) {
                throw std::runtime_error("RPC server is not set");
            }

            command_callbacks_[id] = callback;
            auto message_ptr = rpc_server_->create_message();
            auto& message = *message_ptr;

            message.from().from_string(rpc_server_->get_local_endpoint()->to_string());
            message.to().from_string(params_.user_info_server);
            message.payload(command_json.dump());

            rpc_server_->send(message);
        }

        // user.message_send
        // Checking if the requested field exists and is a string (validation and sanity checks) then we proceed with building the command<->callback tree and sending the message to the remote endpoint, which we form from the information we have from GUI json.
        else if (command_json["command"].is_string() && command_json["command"].get<std::string>() == "message.send") {
            if (!command_json["payload"]["to_ip"].is_string()) {
                nlohmann::json result_json;
                result_json["answer"] = "fail";
                result_json["payload"]["reason"] = "invalid or missing to_ip";
                callback(result_json.dump());
            }

            if (!rpc_server_) {
                throw std::runtime_error("RPC server is not set");
            }

            command_callbacks_[id] = callback;
            auto message_ptr = rpc_server_->create_message();
            auto& message = *message_ptr;

            message.from().from_string(rpc_server_->get_local_endpoint()->to_string());
            message.to().from_string(command_json["payload"]["to_ip"].get<std::string>());
            command_json["payload"].erase("to_ip");
            message.payload(command_json["payload"].dump());

            rpc_server_->send(message);
        }

        else {
            // In case of invalid command.
            nlohmann::json result_json;
            result_json["answer"] = "fail";
            result_json["payload"]["reason"] = "invalid command";
            callback(result_json.dump());
        }
    }

} // namespace chat::implementation

