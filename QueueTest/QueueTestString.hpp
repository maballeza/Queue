#pragma once
#include "gtest/gtest.h"
#include "../Queue.hpp"
#include <string>

/**
* class QueueTestString
*   Specialized test for a string implementation of the Queue interface.
*/
class QueueTestString : public testing::Test {
public:
    template <typename I>
    using N      = BiDirectionalNode<I>;
    using string = std::string;
    using Queue  = Queue<N, string>;
    using Handle = HNode<N, string>;

    void SetUp() override {
        for (string& item : keys) { // Initializes test_Q.
            Handle n = Build<N, string>::Instance(std::move(item));
            test_Q.Enqueue(n.Release());
        }
    }

    Queue test_Q;
    std::vector<string> keys { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
};