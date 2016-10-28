#pragma once

#include <mutex>
#include <condition_variable>

class RingBuffer {
public:
    RingBuffer(int capacity);
    ~RingBuffer();

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

    void add(char val);
    char get();
};