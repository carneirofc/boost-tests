#include <memory>
#include "log/Logger.hpp"
#include "net/Server.hpp"

int main(int argc, char* argv[]){
    Utils::Logger::Init();
    //if(argc != 2){
    //    LOG_ERROR("Params: <port>");
    //    return -1;
    //}
    std::shared_ptr<Net::Server> server;
    server->listen(5000);
    return 0;
}