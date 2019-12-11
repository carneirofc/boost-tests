#include "log/Logger.hpp"

#include <boost/asio.hpp>

namespace Net{
    class Server{
        public:
            void listen(const int port);
        private:
            void write(boost::asio::ip::tcp::socket& socket,const std::string& message);
            std::string read(boost::asio::ip::tcp::socket& socket);
            virtual void handle(boost::asio::ip::tcp::socket& socket,const std::string& message);
    };
}