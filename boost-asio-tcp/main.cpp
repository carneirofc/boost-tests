#include <memory>
#include <regex>
#include <string>
#include "log/Logger.hpp"
#include "net/Handler.hpp"
#include "net/Server.hpp"
// #include "boost/regex.hpp"
// #include "boost/lexical_cast.hpp"

class CustomHandler: public Net::Handler{
    public:
        CustomHandler() : m_regMatch(std::regex("set value\\d+ (.*)\n")){}
    private:
        const char* GET = "get";
        const char* SET = "set";

        std::regex m_regMatch;
        const std::string handle(boost::asio::ip::tcp::socket& socket, const std::string& message) override final{
            try{
                // message.starts_with(GET);
                std::smatch m_smatch; 
                if(std::regex_match(message, m_smatch, m_regMatch, std::regex_constants::match_default)
                    && m_smatch.size() == 2){
                    LOG_INFO("{}", m_smatch[1].str());
                    return "ACK\n";
                }
                
                LOG_WARN("Invalid command {}", message);
                return "NACK\n";

            } catch (std::regex_error& e) {
                LOG_CRITICAL("Exception: {}.", e.what());

                return fmt::format("EXCEPTION: Malformed regex {}.", e.what());
                // Syntax error in the regular expression
            }
        }
};

int main(int argc, char* argv[]){
    Utils::Logger::Init();
    std::shared_ptr<Net::Server> server = 
        std::make_shared<Net::Server>(std::make_shared<CustomHandler>());
    server->listen(5000);
    return 0;
}