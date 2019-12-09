//
// Created by carneirofc on 05/12/2019.
//
#include <memory>

#include "Logger.hpp"
#include "Comm.hpp"

int main(){
    Regatron::Logger::Init();

    try {
        auto reg = std::make_unique<Regatron::Comm>();
        reg->moduleIDInfo();
        reg->connect(1);
    }catch (std::runtime_error &e){
        REG_LOG_CRITICAL("Exception: {}", e.what());
    }

    return 0;
}
