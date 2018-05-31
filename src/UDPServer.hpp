#pragma once

#include "json.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <functional>
#include <string>
#include <vector>

#include <cassert>
#include <cstdint>


// Message struct used for UDPServer service, payload can be any
struct Message {
    boost::asio::ip::udp::endpoint from;
    boost::asio::ip::udp::endpoint to;
    nlohmann::json payload;
};

class MessageHandlerBase {
public:
    virtual ~MessageHandlerBase() = default;
    virtual void handle(const Message&) = 0;
};

class UDPServer {
public:
    explicit UDPServer(boost::asio::io_service& io_service, const std::uint16_t port = 8080)
        : socket_(io_service)
        , port_(port)
    {
    }
    
    ~UDPServer() {
        stop();
    }

    boost::asio::ip::udp::endpoint get_default_local_endpoint() const {
        return socket_.local_endpoint();
    }
    
    void start() {
        const boost::asio::ip::udp::endpoint ep(boost::asio::ip::udp::v4(), port_);
        socket_.open(ep.protocol());
        socket_.bind(ep);
        receive(); // ...asynchroniously listen for the first message
    }
    
    void stop() {
        socket_.close();
    }
    
    void send(const Message& message) {
        assert(message.from == socket_.local_endpoint());
        
        send_buffer_tmp_.clear();
        serialize(message, send_buffer_tmp_);
        socket_.async_send_to(
                              boost::asio::buffer(send_buffer_tmp_),
                              message.to,
                              boost::bind(
                                          &UDPServer::send_handler,
                                          this,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred,
                                          send_buffer_tmp_.size()
                                          )
                              );
    }
    
    void set_message_handler(MessageHandlerBase* message_handler) {
        message_handler_ = message_handler;
    }
    
private:
    void receive() {
        receive_buffer_tmp_.resize(2048); // UDP datagram payload max size accepted by this code
        socket_.async_receive_from(
                                   boost::asio::buffer(receive_buffer_tmp_),
                                   remote_endpoint_tmp_,
                                   boost::bind(
                                               &UDPServer::receive_handler,
                                               this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred
                                               )
                                   );
    }
    
    void receive_handler(const boost::system::error_code& error_code, std::size_t bytes_transferred) {
        if (error_code) {
            if (error_code != boost::asio::error::operation_aborted) {
                // TODO: asio receive error!
            }
        }
        else {
            Message message_tmp;
            receive_buffer_tmp_.resize(bytes_transferred);
            deserialize(receive_buffer_tmp_, message_tmp);
            message_tmp.from = remote_endpoint_tmp_;
            message_tmp.to = socket_.local_endpoint();
            
            // Process this one.
            if (message_handler_) {
                message_handler_->handle(message_tmp);
            }
            
            receive(); // ...asynchroniously listen for the next one
        }
    }
    
    void send_handler(const boost::system::error_code& error_code, std::size_t bytes_transferred, std::size_t bytes_should_be_transferred) {
        if (error_code) {
            if (error_code != boost::asio::error::operation_aborted) {
                // TODO: asio send error!
            }
        }
        else if (bytes_transferred != bytes_should_be_transferred) {
            // TODO: asio hasn't sent the entire payload!
        }
        else {
            // message has been sent...
        }
    }
    
    static void serialize(const Message& message, std::vector<std::uint8_t>& buffer) {
        auto str = message.payload.dump();
        buffer.reserve(buffer.size() + str.size());
        std::copy(str.begin(), str.end(), std::back_inserter(buffer));
    }
    
    static void deserialize(const std::vector<std::uint8_t>& buffer, Message& message) {
        const std::string str(buffer.begin(), buffer.end());
        message.payload = nlohmann::json::parse(str);
    }
    
private:
    boost::asio::ip::udp::socket socket_;
    const std::uint16_t port_;
    MessageHandlerBase* message_handler_ = nullptr;
    
    boost::asio::ip::udp::endpoint remote_endpoint_tmp_;
    std::vector<std::uint8_t> send_buffer_tmp_;
    std::vector<std::uint8_t> receive_buffer_tmp_;
};
