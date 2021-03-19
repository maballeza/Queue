#include <iostream>
#include "Queue.hpp"

int main()
{
    Queue<int> q;
    Queue<float> qf;
    
    int size = 100;
    while (size) {
        q.Enqueue(size--);
    }
    float f = 0;
    while (f < 10)
    {
        f = f + 0.1f;
        qf.Enqueue(static_cast<float&&>(f));
    }

    while (auto v = q.Dequeue()) {
        std::cout << *v << std::endl;
    }
    while (auto v = qf.Dequeue()) {
        std::cout << *v << std::endl;
    }
}