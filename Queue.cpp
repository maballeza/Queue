#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "Queue.hpp"

template<typename T>
using Node = DirectedNode<T>;

int main()
{
    {
        Queue<char> qc;
        Queue<int> qi;
        Queue<float> qf;
        Queue<std::string> qs;

        const int size = 10;
        // std::array<char, size> charA;
        // std::array<int, size> intA;
        // std::array<float, size> floatA;
        // std::array<std::string, size> strA;
        
        std::vector<Node<char>*> before_after{};

        for (int sz = 0; sz < size; sz++) {
            char ch = sz;
            float f = sz;  // Widening.
            std::string name{ std::to_string(ch) };
#ifdef BUILD
            auto cNode = Node<char>::Build(std::move(ch));
            auto iNode = Node<int>::Build(std::move(sz));
            auto fNode = Node<float>::Build(std::move(f));
            auto sNode = Node<std::string>::Build(std::move(name));

            qc.Enqueue(cNode);
            qi.Enqueue(iNode);
            qf.Enqueue(fNode);
            qs.Enqueue(sNode);

            before_after.emplace_back(cNode);
#endif
#ifndef BUILD
            qc.Enqueue(std::move(ch));
            qi.Enqueue(std::move(sz));
            qf.Enqueue(std::move(f));
            qs.Enqueue(std::move(name));
#endif
        }

        auto cc{ std::move(qc) };
        auto ci{ std::move(qi) };
        auto cf{ std::move(qf) };
        auto cs{ std::move(qs) };
#ifdef BUILD
        int count = cc.Size();
        while (count--) {
            before_after.emplace_back(cc.Dequeue());
        }
#endif
    }
} 

void Test() {
    {
        Queue<char> qc;
        Queue<int> qi;
        Queue<float> qf;
        Queue<std::string> qs;

        const int size = 10;
        for (int sz = 0; sz < size; sz++) {
            char ch = sz;
            float f = sz;  // Widening.
            std::string name{ std::to_string(ch) };
#ifndef BUILD
            qc.Enqueue(std::move(ch));
            qi.Enqueue(std::move(sz));
            qf.Enqueue(std::move(f));
            qs.Enqueue(std::move(name));
#endif
        }

        auto cc{ std::move(qc) };
        auto ci{ std::move(qi) };
        auto cf{ std::move(qf) };
        auto cs{ std::move(qs) };

        // TODO
        //for (int sz = 0; sz < size; sz++) {
        //    if (charA[sz] !=  (qc.Dequeue()).item) throw;
        //    if (intA[sz] !=   (qi.Dequeue()).item) throw;
        //    if (floatA[sz] != (qf.Dequeue()).item) throw;
        //    if (strA[sz] !=   (qs.Dequeue()).item) throw;
        //}
    }
} 