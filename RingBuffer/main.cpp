#include "RingBuffer.h"
#include <thread>

//void puttNoeInnIRB(RingBuffer& rb) {
//    rb.inputKeyboard();
//}

int main() {
    RingBuffer obj(10);

    //std::thread T1(&RingBuffer::inputKeyboard, &obj);
    
    //std::thread T1(puttNoeInnIRB, std::ref(obj));
    //std::thread T1(obj.inputKeyboard);
    //std::thread T2(obj.autoInput);
    //std::thread T3(obj.readBuffer);

    std::thread T1([&obj] {
        obj.inputKeyboard();
    });
    std::thread T2([&obj] {
        obj.autoInput();
    });
    std::thread T3([&obj] {
        obj.readBuffer();
    });

    T1.join();
    T2.join();
    T3.join();


    //3 ut av 8 threads

}
