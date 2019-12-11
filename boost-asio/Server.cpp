#include "Server.hpp"
#include "Logger.hpp"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace Server {

    std::string Server::read(boost::asio::ip::tcp::socket& socket){
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n" );
        std::string data = boost::asio::buffer_cast<const char*>(buf.data());
        return data;
    }

    void Sever::send(boost::asio::ip::tcp::socket& socket, const std::string& message){
       const std::string msg = message + "\n";
       boost::asio::write(socket, boost::asio::buffer(message));
    }

    void Server::serve(int port){
        boost::asio::io_service io_service;
        //listen for new connection
        boost::asio::ip::tcp::acceptor acceptor_(io_service,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 5000));
        //socket creation 
        boost::asio::ip::tcp::socket socket_(io_service);
        //waiting for connection
        acceptor_.accept(socket_);
        //read operation
        std::string message = Server::read(socket_);
        LOG_INFO("From client: {}", message);
        //write operation
        Server::send(socket_, "Hello From Server!");
    }
}