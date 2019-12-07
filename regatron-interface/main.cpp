//
// Created by carneirofc on 05/12/2019.
//
#include <bits/unique_ptr.h>
#include "boost/log/trivial.hpp"
#include "Regatron.hpp"

int main(){
    try {
        auto reg = std::make_unique<Regatron>();
        reg->moduleIDInfo();
        reg->connect(1);
    }catch (std::runtime_error &e){
        BOOST_LOG_TRIVIAL(fatal) <<"Exception: "<< e.what();
    }

    return 0;
}
