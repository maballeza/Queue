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

        charA[sz] = *qc.Enqueue(std::move(ch));
        intA[sz] = *qi.Enqueue(std::move(sz));
        floatA[sz] = *qf.Enqueue(std::move(f));
        strA[sz] = *qs.Enqueue(std::move(name));
    }

    for (int sz = 0; sz < size; sz++) {
        if (charA[sz] != qc.Dequeue()) throw;
        if (intA[sz] != qi.Dequeue()) throw;
        if (floatA[sz] != qf.Dequeue()) throw;
        if (strA[sz] != qs.Dequeue()) throw;
    }
}