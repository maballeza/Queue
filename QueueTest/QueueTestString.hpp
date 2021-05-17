#pragma once
#include "gtest/gtest.h"
#include "../Queue.hpp"
#include <numeric>

/**
* class QueueTestString
*   Specialized test for a string implementation of the Queue interface.
*/
class QueueTestString : public testing::Test {
public:
    void SetUp() override {
        std::vector<int> ints;
        // Initialize 'vals' with values { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.
        ints.resize(10);
        std::iota(ints.begin(), ints.end(), 0);
        // Initialize 'Q.'
        for (auto& v : ints) {
            std::string s = std::to_string(v);
            vals.emplace_back(s);
            Q.Enqueue(std::move(s));
        }
    }

    Queue<std::string> Q;
    std::vector<std::string> vals;
};