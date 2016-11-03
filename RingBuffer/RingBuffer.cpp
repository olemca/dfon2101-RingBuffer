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
        full_cv.wait(lock); //if buffer is full - wait
    }

    buffer[in] = val;
    in = (in + 1) % bufferSize;

    empty_cv.notify_one();
}

char RingBuffer::get() {
    std::unique_lock<std::mutex> lock(mutex); //Lock mutex
    while (in == out) {
        empty_cv.wait(lock); //While empty - wait
    }

    char consumed = buffer[out];
    out = (out + 1) % bufferSize;

    full_cv.notify_one();

    return consumed;
}

void RingBuffer::inputKeyboard() {
    while (run) { //run is true makes it keep running the function
        std::string tekst;
        std::getline(std::cin, tekst); //adds what i type into string tekst
        if (tekst == "stop") { //"stop" is my command to shut down program
            run = false;
        }
        for (unsigned int i = 0; i < tekst.length(); i++) {
            add(tekst[i]); //puts each char of tekst into add() function
        }
    }
}

void RingBuffer::autoInput() {
    while (run) { //run is true, makes the function keep going
        add((rand() % 26) + 97); //adds some random letters
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); //500ms pause
    }
}

void RingBuffer::readBuffer() {
    while (run) { //run is true, which makes it continue reading buffer
        char thc = get();
        std::cout << thc;
    }
}