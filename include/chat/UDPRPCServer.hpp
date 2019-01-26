#pragma once

#include <chat/RPCServer.hpp>

#include <nlohmann/json.hpp>

#include <boost/asio.hpp>

#include <string>
#include <vector>

#include <cstdint>


namespace chat::implementation {

    class UDPRPCServer : public interface::RPCServer {
    public:
        struct Params {
            explicit Params(const nlohmann::json& config_json = nlohmann::json());

            std::uint16_t port = 8080;
        };

        class Endpoint : public interface::RPCServer::Endpoint {
        public:
            virtual void from_string(const std::string& str) override;
            virtual std::string to_string() const override;

            boost::asio::ip::udp::endpoint endpoint_;
        };

        class Message : public interface::RPCServer::Message {
        public:
            virtual interface::RPCServer::Endpoint& from() override;
            virtual interface::RPCServer::Endpoint& to() override;
            virtual const std::string& payload() const override;
            virtual void payload(const std::string& str) override;

            Endpoint from_;
            Endpoint to_;
            std::string payload_;
        };

        UDPRPCServer(const Params& params, boost::asio::io_service& io_service);
        virtual ~UDPRPCServer();

        virtual void start() override;
        virtual void stop() override;

        virtual std::shared_ptr<interface::RPCServer::Message> create_message() const override;
        virtual std::shared_ptr<interface::RPCServer::Endpoint> get_local_endpoint() const override;

        virtual void send(const interface::RPCServer::Message& message) override;
        void send(const Message& message);

    private:
        void receive();
        void receive_handler(const boost::system::error_code& error_code, std::size_t bytes_transferred);
        void send_handler(const boost::system::error_code& error_code, std::size_t bytes_transferred, std::size_t bytes_should_be_transferred);

    private:
        const Params params_;
        boost::asio::ip::udp::socket socket_;

        boost::asio::ip::udp::endpoint remote_endpoint_tmp_;
        std::vector<std::uint8_t> send_buffer_tmp_;
        std::vector<std::uint8_t> receive_buffer_tmp_;
    };

} // namespace chat::implementation

