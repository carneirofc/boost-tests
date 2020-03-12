
#include "net/Handler.hpp"
#include "log/Logger.hpp"

#include "Comm.hpp"

#include  <string>

namespace Regatron{
    class Handler : public Net::Handler{
        public:
            Handler(std::shared_ptr<Regatron::Comm> regatron): regatron(regatron){};
        private:
            std::shared_ptr<Regatron::Comm> regatron;

            #define NACK "NACK\n"
            #define ACK "ACK\n"

            #define GET "get "
            #define SET "set "

            #define VOLTAGE "voltage "
            #define CURRENT "current "

            bool getParam(const std::string message, const char* beg_pattern, const char* complete_pattern, float* res){
                return (message.starts_with(beg_pattern) && (std::sscanf(message.c_str(),complete_pattern, &res) != 1));
            }

            /** Try to get a float from the message based on a patter.
             * This should be used inside Reg::Handler::handle() method!
             * return: true or false
             * throws: May throw something (std::invalid_argument)!
             */
            #define MATCH_SET(pattern) getParam(message, SET pattern, SET pattern "%f\n", &res) 
            #define MATCH_GET(pattern) (message == GET pattern "\n")
            

            const std::string handle(const std::string& message) override{
                float res;
                try{

                    if(message.starts_with(SET)){
                        if(MATCH_SET(VOLTAGE)){
                            /** handle shit */
                            return ACK;
                        }

                    }else if(message.starts_with(SET)){
                        if(MATCH_GET(VOLTAGE)){
                            /** handle shit */
                            return ACK;
                        }
                    }
                    LOG_WARN("No compatible action for {}!", message);
                } catch(const std::invalid_argument& e){
                    LOG_CRITICAL("Exception: Invalid argument {} {}.", message, e.what());
                } catch(const std::runtime_error& e){
                    LOG_CRITICAL("Exception: A bug !{} {}.", message, e.what());
                }
                return NACK;
            }
    };
}
