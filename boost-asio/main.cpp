
#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "Logger.hpp"

void example1(){
    LOG_INFO("Example 1"); 
    // All programs that use asio need to have at least one io_context object
    boost::asio::io_context io;
    /* Next we declare an object of type boost::asio::steady_timer.
        The core asio classes that provide I/O functionality (or as in this case timer functionality)
        always take a reference to an io_context as their first constructor argument.
    The second argument to the constructor sets the timer to expire 5 seconds from now. */
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    
    t.wait();
    LOG_INFO("done!\n"); 
}

void showSomeText(const boost::system::error_code& e){
    LOG_WARN("Wait is over. {}.", e.message());
}

void showSomeText2(const boost::system::error_code& e, boost::asio::steady_timer* t, int* count){
    if (*count < 5){
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(showSomeText2, boost::asio::placeholders::error, t, count));
        LOG_WARN("Wait is over, count {}. {}.", *count, e.message());
        ++(*count);
    }
}

void example2(){
    LOG_INFO("Example 2");
    // Asynchronous callback function
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(2));
    t.async_wait(&showSomeText);
    // we must call the io_context::run() member function on the io_context object.
    io.run();
}

void example3(){
    LOG_INFO("Example 3");
    /*  To implement a repeating timer using asio you need to change the timer's expiry time in your callback function,
    and to then start a new asynchronous wait. */
    int count = 0;
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
    t.async_wait(boost::bind(showSomeText2, boost::asio::placeholders::error, &t, &count));
    io.run();

    LOG_INFO("Final count is {}", count);
}

class Printer{
    private:
        boost::asio::steady_timer timer_;
        int count_;
    
    public:
        Printer(boost::asio::io_context& io)
            : timer_(io, boost::asio::chrono::seconds(1)), count_(0){
                timer_.async_wait(boost::bind(&Printer::print, this));
        }

        ~Printer(){ LOG_INFO("Final count is {}.", count_); }
        
        void print(){
            if (count_ < 5){
                LOG_INFO("Count {}.", count_);
                ++count_;
                timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
                timer_.async_wait(boost::bind(&Printer::print, this));
            }
        }
};

void example4(){
    LOG_INFO("Example 4");
    boost::asio::io_context io;
    Printer p(io);
    io.run();
}

void example5(){
    LOG_INFO("Example 5");
}

int main(){
    Utils::Logger::Init();
    return 0;
}