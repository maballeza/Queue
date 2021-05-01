#include <iostream>
#include <string>
#include <array>
#include "Queue.hpp"

int main()
{
    Queue<char> qc;
    Queue<int> qi;
    Queue<float> qf;
    Queue<std::string> qs;

    const int size = 10;
    std::array<char, size> charA;
    std::array<int, size> intA;
    std::array<float, size> floatA;
    std::array<std::string, size> strA;

    for (int sz = 0;  sz < size; sz++) {
        char ch = sz;
        float f = sz;  // Widening.
        std::string name{ std::to_string(ch) };

        qc.Enqueue(std::move(ch));
        qi.Enqueue(std::move(sz));
        qf.Enqueue(std::move(f));
        qs.Enqueue(std::move(name));
    }

    auto cc{ std::move(qc) };
    auto ci{ std::move(qi) };
    auto cf{ std::move(qf) };
    auto cs{ std::move(qs) };
    
    // TODO
    /*for (int sz = 0; sz < size; sz++) {
        if (charA[sz] !=  qc.Dequeue()) throw;
        if (intA[sz] !=   qi.Dequeue()) throw;
        if (floatA[sz] != qf.Dequeue()) throw;
        if (strA[sz] !=   qs.Dequeue()) throw;
    }*/
} 