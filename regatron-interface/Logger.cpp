#include "Logger.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Regatron {
    std::shared_ptr<spdlog::logger> Logger::defaultLogger;
    
    void Regatron::Logger::Init(){
        defaultLogger = spdlog::stdout_color_mt("Regatron");
        defaultLogger->set_level(spdlog::level::trace);
    }
}