#pragma once

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace Client{
    void run(std::string, std::string);
    std::string read(boost::asio::ip::tcp::socket&);
    void send(boost::asio::ip::tcp::socket&, const std::string&);
}