//
// Created by carneirofc on 05/12/2019.
//
#include "Regatron.hpp"

int main(){
    std::unique_ptr<Regatron> reg = std::make_unique<Regatron>();
    reg->moduleIDInfo();
    reg->connect(1);
    return 0;
}
