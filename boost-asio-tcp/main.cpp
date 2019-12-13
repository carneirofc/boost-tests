#include <memory>
#include "log/Logger.hpp"
#include "net/Handler.hpp"
#include "net/Server.hpp"

class CustomHandler: public Net::Handler{
    private:
        const std::string handle(boost::asio::ip::tcp::socket& socket, const std::string& message) 
            override final{
            LOG_INFO("Okay ... {}", message);
            return "Custom Handler\n";
        }
};

int main(int argc, char* argv[]){
    Utils::Logger::Init();
    std::shared_ptr<Net::Server> server = 
        std::make_shared<Net::Server>(std::make_shared<CustomHandler>());
    server->listen(5000);
    return 0;
}