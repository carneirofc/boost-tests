#include "Client.hpp"
#include "Logger.hpp"

namespace Client{

    std::string read(boost::asio::ip::tcp::socket& socket){
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n" );
        std::string data = boost::asio::buffer_cast<const char*>(buf.data());
        return data;
    }

    void send(boost::asio::ip::tcp::socket& socket, const std::string& message){
       const std::string msg = message + "\n";
       boost::asio::write(socket, boost::asio::buffer(message));
    }

    void connect(std::string host, std::string port){
        try{
            // All programs that use asio need to have at least one io_context object. 
            boost::asio::io_context io;

            /* We need to turn the server name that was specified as a parameter to the application,
            into a TCP endpoint. To do this we use an ip::tcp::resolver object */
            boost::asio::ip::tcp::resolver resolver(io);
            boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, port);

            boost::asio::ip::tcp::socket socket(io);
            boost::asio::connect(socket, endpoints);
            for (;;){
                boost::system::error_code error;

                std::string response = Client::read(socket);
                LOG_INFO("Recv: {}", response);
                Client::send(socket, "client message!");

                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.
            }
        }catch (std::exception& e){
            LOG_CRITICAL("Exception: {}", e.what());
        }
    
    }
}