#include <chat/UDPRPCServer.hpp>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <regex>
#include <sstream>
#include <stdexcept>


namespace chat::detail {

    boost::asio::ip::udp::endpoint from_string(const std::string& str) {
        std::regex rx("udp://(.+):(.+)/*");
        std::smatch matches;

        if(!std::regex_search(str, matches, rx) || matches.size() != 3) {
            throw std::runtime_error("unable to parse '" + str + "' as udp IPv4 endpoint");
        }

        return boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::from_string(matches[1].str()),
                                              boost::lexical_cast<std::uint16_t>(matches[2].str()));
    }

    std::string to_string(const boost::asio::ip::udp::endpoint& endpoint) {
        std::ostringstream str;
        str << "udp" << "://" << endpoint.address() << ":" << endpoint.port();
        return str.str();
    }

    void serialize(const implementation::UDPRPCServer::Message& message, std::vector<std::uint8_t>& buffer) {
        auto& str = message.payload_;
        buffer.reserve(buffer.size() + str.size());
        std::copy(str.begin(), str.end(), std::back_inserter(buffer));
    }

    void deserialize(const std::vector<std::uint8_t>& buffer, implementation::UDPRPCServer::Message& message) {
        const std::string str(buffer.begin(), buffer.end());
        message.payload_ = str;
    }

} // namespace chat::detail

namespace chat::implementation {

    UDPRPCServer::Params::Params(const nlohmann::json& config_json) {
        auto port_it = config_json.find("port");
        if (port_it != config_json.end()) {
            try {
                port = port_it->get<std::uint16_t>();
            }
            catch (const std::exception& ex) {
                throw std::runtime_error("unable to parse port value from config as 16-bit unsigned integer: " + std::string(ex.what()));
            }
        }
    }

    void UDPRPCServer::Endpoint::from_string(const std::string& str) {
        endpoint_ = detail::from_string(str);
    }

    std::string UDPRPCServer::Endpoint::to_string() const {
        return detail::to_string(endpoint_);
    }

    interface::RPCServer::Endpoint& UDPRPCServer::Message::from() {
        return from_;
    }

    interface::RPCServer::Endpoint& UDPRPCServer::Message::to() {
        return to_;
    }

    const std::string& UDPRPCServer::Message::payload() const {
        return payload_;
    }

    void UDPRPCServer::Message::payload(const std::string& str) {
        payload_ = str;
    }

    UDPRPCServer::UDPRPCServer(const Params& params, boost::asio::io_service& io_service)
        : params_(params)
        , socket_(io_service)
    {
    }

    UDPRPCServer::~UDPRPCServer() {
        stop();
    }

    void UDPRPCServer::start() {
        stop();

        const boost::asio::ip::udp::endpoint ep(boost::asio::ip::udp::v4(), params_.port);
        socket_.open(ep.protocol());
        socket_.bind(ep);
        receive(); // ...asynchroniously listen for the first message.
    }

    void UDPRPCServer::stop() {
        socket_.close();
    }

    std::shared_ptr<interface::RPCServer::Message> UDPRPCServer::create_message() const {
        return std::static_pointer_cast<interface::RPCServer::Message>(std::make_shared<Message>());
    }

    std::shared_ptr<interface::RPCServer::Endpoint> UDPRPCServer::get_local_endpoint() const {
        auto endpoint = std::make_shared<Endpoint>();
        endpoint->endpoint_ = socket_.local_endpoint();
        return std::static_pointer_cast<interface::RPCServer::Endpoint>(endpoint);
    }

    void UDPRPCServer::send(const interface::RPCServer::Message& message) {
        try {
            send(dynamic_cast<const Message&>(message));
        }
        catch (const std::bad_cast&) {
            throw std::runtime_error("Unable to send the message: bad message object");
        }
    }

    void UDPRPCServer::send(const Message& message) {
        assert(message.from_.endpoint_ == socket_.local_endpoint());

        send_buffer_tmp_.clear();
        detail::serialize(message, send_buffer_tmp_);
        socket_.async_send_to(
                              boost::asio::buffer(send_buffer_tmp_),
                              message.to_.endpoint_,
                              boost::bind(
                                          &UDPRPCServer::send_handler,
                                          this,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred,
                                          send_buffer_tmp_.size()
                                          )
                              );
    }

    void UDPRPCServer::receive() {
        // Maximum supported UDP datagram payload size: 0xffff - (sizeof(smallest possible IPv4 Header) + sizeof(UDP Header)) = 65535 - (20 + 8) = 65507.
        const std::size_t udp_datagram_max_payload_size = 65507;
        receive_buffer_tmp_.resize(udp_datagram_max_payload_size);
        socket_.async_receive_from(
                                   boost::asio::buffer(receive_buffer_tmp_),
                                   remote_endpoint_tmp_,
                                   boost::bind(
                                               &UDPRPCServer::receive_handler,
                                               this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred
                                               )
                                   );
    }

    void UDPRPCServer::receive_handler(const boost::system::error_code& error_code, std::size_t bytes_transferred) {
        if (error_code) {
            if (error_code != boost::asio::error::operation_aborted) {
                throw std::runtime_error("Asio receive error: " + error_code.message());
            }
        }
        else {
            Message message_tmp;
            receive_buffer_tmp_.resize(bytes_transferred);
            detail::deserialize(receive_buffer_tmp_, message_tmp);
            message_tmp.from_.endpoint_ = remote_endpoint_tmp_;
            message_tmp.to_.endpoint_ = socket_.local_endpoint();

            // Process this one.
            process_received(static_cast<interface::RPCServer::Message&>(message_tmp));

            receive(); // ...asynchroniously listen for the next one.
        }
    }

    void UDPRPCServer::send_handler(const boost::system::error_code& error_code, std::size_t bytes_transferred, std::size_t bytes_should_be_transferred) {
        if (error_code) {
            if (error_code != boost::asio::error::operation_aborted) {
                throw std::runtime_error("Asio send error: " + error_code.message());
            }
        }
        else if (bytes_transferred != bytes_should_be_transferred) {
            throw std::runtime_error("Asio send error: the entire payload has not been sent");
        }
        else {
            // The message has been sent...
        }
    }

} // namespace chat::implementation



