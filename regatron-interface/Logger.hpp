#pragma once

#include <memory>
#include "spdlog/spdlog.h"

namespace Regatron{
    class Logger{
    private:
        static std::shared_ptr<spdlog::logger> defaultLogger;

    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& getLogger() { return defaultLogger; }
    };
}

#define REG_LOG_TRACE(...)    ::Regatron::Logger::getLogger()->trace(__VA_ARGS__)
#define REG_LOG_INFO(...)     ::Regatron::Logger::getLogger()->info(__VA_ARGS__)
#define REG_LOG_WARN(...)     ::Regatron::Logger::getLogger()->warn(__VA_ARGS__)
#define REG_LOG_ERROR(...)    ::Regatron::Logger::getLogger()->error(__VA_ARGS__)
#define REG_LOG_CRITICAL(...) ::Regatron::Logger::getLogger()->critical(__VA_ARGS__)