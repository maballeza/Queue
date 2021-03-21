#include <iostream>
#include "Queue.hpp"

int main()
{

    Queue<int> q;
    Queue<float> qf;
    
    int size = 100;
    float f = 0;
    while (size) {
        f = f + 0.1f;
        q.Enqueue(size--);
        qf.Enqueue(static_cast<float&&>(f));
    }

    while (auto v = q.Dequeue()) {
        std::cout << *v << std::endl;
    }
    while (auto v = qf.Dequeue()) {
        std::cout << *v << std::endl;
    }
}