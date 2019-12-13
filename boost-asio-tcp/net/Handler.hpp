
#pragma once

#include "boost/asio.hpp"

namespace Net{
    class Handler{
        public:
            virtual const std::string handle(boost::asio::ip::tcp::socket& socket, const std::string& message);
    };
} // namespace nameNe
