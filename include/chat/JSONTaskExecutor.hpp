#pragma once

#include <chat/TaskExecutor.hpp>

#include <nlohmann/json.hpp>

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <string>


namespace chat::implementation {

    class JSONTaskExecutor : public interface::TaskExecutor {
    public:
        struct Params {
            explicit Params(const nlohmann::json& config_json = nlohmann::json());

            std::string user_info_server = "udp://91.211.107.158:1337";
        };

        JSONTaskExecutor(const Params& params, boost::asio::io_service& io_service);
        virtual ~JSONTaskExecutor();

        virtual void start() override;
        virtual void stop() override;

        virtual void handle(const interface::RPCServer::Message& message) override;
        virtual void execute_async(const std::string& command, const Callback& callback) override;

    private:
        void execute(nlohmann::json command_json, const Callback& callback);

    private:
        const Params params_;
        boost::asio::io_service& io_service_;
        std::map<std::string, Callback> command_callbacks_; // Map of command<->callback, to be used in handle and execute.
    };

} // namespace chat::implementation

