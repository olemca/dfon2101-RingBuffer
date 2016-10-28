#include "RingBuffer.h"
#include <string>
#include <iostream>

RingBuffer::RingBuffer(int capacity) {
    buffer = new char[capacity];
    bufferSize = capacity;
    run = true;
}

RingBuffer::~RingBuffer() {
    if (buffer != nullptr) {
        delete[] buffer;
    }
}

void RingBuffer::add(char val) {
    std::unique_lock<std::mutex> lock(mutex); //Lock mutex
    if ((in + 1) % bufferSize == out) {
        full_cv.wait(lock);
    }

    buffer[in] = val;
    in = (in + 1) % bufferSize;

    empty_cv.notify_one();
}

char RingBuffer::get() {
    std::unique_lock<std::mutex> lock(mutex); //Lock mutex
    while (in == out) {
        empty_cv.wait(lock); //Wait until buffer is not empty
    }

    char consumed = buffer[out];
    out = (out + 1) % bufferSize;

    full_cv.notify_one();

    return consumed;
}

void RingBuffer::inputKeyboard() {
    while (run) {
        std::string tekst;
        std::getline(std::cin, tekst);
        if (tekst == "stop") {
            run = false;
        }
        for (unsigned int i = 0; i < tekst.length(); i++) {
            add(tekst[i]);
        }
    }
}

void RingBuffer::autoInput() {
    while (run) {
        add((rand() % 26) + 97);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void RingBuffer::readBuffer() {
    while (run) {
        char thc = get();
        std::cout << thc;
    }
}
