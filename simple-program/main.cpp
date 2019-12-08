
#include <iostream>
#include <functional>
#include "fmt/format.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
int main(){
   // C++11
    [out = std::ref(std::cout << "Hello World")](){ out.get() << "!\n"; }();
    
    // Fmt
    fmt::print("Hello {}!\n", "World");

    std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
    std::cout << s << '\n';

    // spdlog
    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");
};