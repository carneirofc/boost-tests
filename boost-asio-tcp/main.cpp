#include <memory>
#include <regex>
#include <string>
#include <stdexcept>

#include "log/Logger.hpp"
#include "net/Handler.hpp"
#include "net/Server.hpp"

class CustomHandler: public Net::Handler{
    public:
        CustomHandler() :
            //m_regSetValue(std::regex("set float (\\d+\.\\d*)\n")),
            m_regSetValue(std::regex("set float (\\d+\.\\d*)\n")),
            m_regGetValue(std::regex("get float\n"))
            {}
    private:

        std::regex m_regSetValue;
        std::regex m_regGetValue;

        #define NACK "NACK\n"
        #define ACK "ACK\n"
        
        #define MATCH_GET(M_REG) if(std::regex_match(message, m_smatch, M_REG, std::regex_constants::match_default))
        #define MATCH_SET(M_REG) if(std::regex_match(message, m_smatch, M_REG, std::regex_constants::match_default)\
                    && m_smatch.size() == 2)
        
        #define SET_FLOAT "set float_test "

        const float getParam(const char* message, const char* pattern, float* res){
         if(std::sscanf(message, pattern, &res) != 1){
            throw std::invalid_argument(fmt::format("Malformed command! {}", message));
         }
         /*if(message.starts_with(prefix)){
            std::string_view strVal = message;
            strVal.remove_prefix(prefix.size());
            if(strVal.ends_with("\n")){ strVal.remove_suffix(1);}
            return std::stof(strVal);
         }
         */
        }

        const std::string handle(const std::string& message) override{
            try{
                std::smatch m_smatch;

                MATCH_SET(m_regSetValue){
                    LOG_INFO("Param {}", std::stof(m_smatch[1].str()));
                    return ACK;
                }
                MATCH_GET(m_regGetValue){
                    return ACK;
                }

                float res;
                if(message.starts_with(SET_FLOAT)){
                    res = getParam(message.c_str(), SET_FLOAT "%f\n", &res);
                    LOG_INFO("Param {}", res);
                    return ACK;
                }

                LOG_WARN("No compatible action for {}!", message);
            } catch (const std::regex_error& e) {
                LOG_CRITICAL("EXCEPTION: Malformed regex {} {}.", message, e.what());
            } catch(const std::invalid_argument& e){
                LOG_CRITICAL("Exception: Invalid argument {} {}.", message, e.what());
            } catch(const std::runtime_error& e){
                LOG_CRITICAL("Exception: A bug !{} {}.", message, e.what());
            }
            return NACK;
        }
};

int main(int argc, char* argv[]){
    Utils::Logger::Init();
    
    int port = 5000;
    if(argc == 2){
        try{
            port = std::stoi(argv[1]);
        }catch(const std::invalid_argument& e){
            LOG_CRITICAL("Invalid argument {}.", e.what());
        }
    }

    std::shared_ptr<Net::Handler> handler= std::make_shared<CustomHandler>();
    std::shared_ptr<Net::Server> server = std::make_shared<Net::Server>(handler);
    server->listen(port);
    return 0;
}