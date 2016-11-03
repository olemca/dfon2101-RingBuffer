#pragma once //Prevent header file from being included multiple times

#include <mutex> //We use mutexes so mutliple threads can use same variables
#include <condition_variable> //Condition variables for 

class RingBuffer {
public:
    RingBuffer(int capacity); //Constructor
    ~RingBuffer(); //Destructor

    void inputKeyboard();
    void autoInput();
    void readBuffer();

private:
    std::mutex mutex;
    std::condition_variable full_cv;
    std::condition_variable empty_cv;

    char * buffer;

    int bufferSize;
    int in = 0;
    int out = 0;
    bool run;
    /*I like have this boolean for purpose of starting functions and
        shutting down program.*/


    /*Decided to have them private*/
    void add(char val);
    char get();
};