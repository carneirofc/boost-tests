
#include <iostream>
#include <functional>

int main(){
    [out = std::ref(std::cout << "Hello World")](){ out.get() << "!\n"; }();
}