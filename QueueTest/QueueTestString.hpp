#pragma once
#include "gtest/gtest.h"
#include "../Queue.hpp"
#include <string>
#include <numeric>

/**
* class QueueTestString
*   Specialized test for a string implementation of the Queue interface.
*/
class QueueTestString : public testing::Test {
public:
    template <typename I>
    using N = BiDirectionalNode<I>;
    using string = std::string;

    void SetUp() override {
        keys.resize(10);
        std::iota(keys.begin(), keys.end(), 0);
        for (std::string& item : keys) { // Initializes 'test_Q' with values { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.
            HNode<N, std::string> n = Build<N, std::string>::Instance(std::move(item));
            test_Q.Enqueue(n.Release());
        }
    }

    Queue<N, std::string> test_Q;
    std::vector<std::string> keys;
};