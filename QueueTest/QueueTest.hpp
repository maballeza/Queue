#pragma once
#include "gtest/gtest.h"
#include "../Queue.hpp"
#include <numeric>

/**
* class QueueTest
*   Type parameterized test for the Queue interface.
*/
template<typename T>
class QueueTest : public testing::Test {
public:
    void SetUp() override {
        // Initialize 'vals' with values { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.
        vals.resize(10);
        std::iota(vals.begin(), vals.end(), 0);
        // Initialize 'Q.'
        for (auto& v : vals) {
            Q.Enqueue(std::move(v));
        }
    }

    Queue<T> Q;
    std::vector<T> vals;
};

TYPED_TEST_SUITE_P(QueueTest);

/**
* Default Constructor
*   Constructs an empty Queue.
*/
TYPED_TEST_P(QueueTest, DefaultConstructor) {
    using T = TypeParam;
    
    Queue<T> q;
    EXPECT_EQ(0, q.Size());
    EXPECT_EQ(T{ -1 }, q.Dequeue().item);
}

/**
* Move Constructor
*   Copies values and dequeues the source Queue.
*/
TYPED_TEST_P(QueueTest, MoveConstructor) {
    using T = TypeParam;

    // Ensure sizes match between the "move-from" and the "moved-to" Queues.
    int QSize = this->Q.Size();
    Queue<T> q{ std::forward<Queue<T>>(this->Q) };
    EXPECT_EQ(q.Size(), QSize);
    
    // Ensure "Dequeue-ing" is performed when the "moved-from" Queue is moved.
    EXPECT_EQ(0, this->Q.Size());
    
    // Check the "moved-to" Queue value-matches the values used to initialize 'Q.'
    for (T& v : this->vals) {
        EXPECT_EQ(v, q.Dequeue().item);
    }
}


/**
* Size()
*   Returns the size of the Queue.
*/
TYPED_TEST_P(QueueTest, Size) {
    using T = TypeParam;
    
    // Empty Queue.
    Queue<T> q;
    EXPECT_EQ(0, q.Size());
    
    // Non-Empty Queue.
    int arbitrary = 20;
    for (int v = 0; v < arbitrary; ++v) {
        q.Enqueue(std::move(v));
    }
    EXPECT_EQ(arbitrary, q.Size());
}

/**
* Enqueue()
*   Moves values into the Queue by r-value reference.
*/
TYPED_TEST_P(QueueTest, Enqueue) {
    using T = TypeParam;
    
    Queue<T> q;
    std::vector<T> clone;
    for (auto& v : this->vals) {
        q.Enqueue(std::forward<T>(v));
        clone.emplace_back(v);
        EXPECT_EQ(clone.size(), q.Size());
    }
}

/**
* Dequeue()
*   Returns a Queue node with a valid value or -1.
*/
TYPED_TEST_P(QueueTest, Dequeue) {
    using T = TypeParam;

    // Ensure a call to Dequeue() from an empty Queue returns -1.
    Queue<T> q;
    EXPECT_EQ(T{ -1 }, q.Dequeue().item);
    
    // 1. Compare values of Q with those of initialization vector 'vals.'
    for (T& v : this->vals) {
        EXPECT_EQ(v, this->Q.Dequeue().item);
    }
    
    // 2. Ensure Q is empty.
    EXPECT_EQ(0, this->Q.Size());
    EXPECT_EQ(T{ -1 }, this->Q.Dequeue().item);
}