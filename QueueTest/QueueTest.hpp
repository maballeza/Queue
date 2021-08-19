#pragma once
#include "gtest/gtest.h"
#include "../Queue.hpp"
#include <numeric>

/**
* class QueueTest
*   Type parameterized test for the queue interface.
*/
template <typename I>
class QueueTest : public testing::Test {
public:
    using N = BiDirectionalNode;

    void SetUp() override {
        keys.resize(10);
        std::iota(keys.begin(), keys.end(), 0);
        for (I& item : keys) { // Initializes 'test_Q' with values { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.
            HNode<N, I> n = Build<N, I>::Instance(std::move(item));
            test_Q.Enqueue(n.Release());
        }
    }

    Queue<N, I> test_Q;
    std::vector<I> keys;
};

TYPED_TEST_SUITE_P(QueueTest);

/**
* Default Constructor
*   Constructs an empty queue.
*/
TYPED_TEST_P(QueueTest, DefaultConstructor) {
    using I    = TypeParam;
    using N    = BiDirectionalNode;
    using Node = BiDirectionalNode<I>;
    
    Queue<N, I> q;
    EXPECT_EQ(0, q.Size());
    
    Node* n = q.Dequeue();
    EXPECT_EQ(nullptr, n);
}

/**
* Move Constructor
*   Clones values and dequeues the source queue.
*/
TYPED_TEST_P(QueueTest, MoveConstructor) {
    using I              = TypeParam;
    using N              = BiDirectionalNode;
    using Node           = BiDirectionalNode<I>;
    std::vector<I>& keys = this->keys;
    Queue<N, I>& test_Q  = this->test_Q;

    // Ensure sizes do not match between the "moved-from" and the "moved-to" queues.
    Queue<N, I> q{ std::forward<Queue<N, I>>(test_Q) };
    EXPECT_NE(q.Size(), test_Q.Size());
    
    // Ensure "Dequeue-ing" is performed when the "moved-from" queue is moved.
    EXPECT_EQ(0, test_Q.Size());
    
    // Check the values used to initialize 'test_Q' and the "moved-to" queue's values match.
    Queue<N, I> cleanup_Q;
    for (I& item : keys) {
        Node* n = q.Dequeue();  // Releases allocated nodes.
        EXPECT_EQ(item, n->item);
        cleanup_Q.Enqueue(n);   // Performs deallocation.
    }
}


/**
* Size()
*   Returns the size of the queue.
*/
TYPED_TEST_P(QueueTest, Size) {
    using I = TypeParam;
    using N = BiDirectionalNode;
    
    // Empty queue.
    Queue<N, I> q;
    EXPECT_EQ(0, q.Size());
    
    // Non-empty queue.
    int arbitrary = 20;
    for (int item = 0; item < arbitrary; ++item) {
        HNode<N, I> n = Build<N, I>::Instance(std::forward<I>(item));
        q.Enqueue(n.Release());
    }
    EXPECT_EQ(arbitrary, q.Size());
}

/**
* Enqueue()
*   Moves values into the queue.
*/
TYPED_TEST_P(QueueTest, Enqueue) {
    using I              = TypeParam;
    using N              = BiDirectionalNode;
    std::vector<I>& keys = this->keys;
    
    Queue<N, I> q;
    std::vector<I> clone;
    for (I& item : keys) {
        HNode<N, I> n = Build<N, I>::Instance(std::forward<I>(item));
        q.Enqueue(n.Release());
        clone.emplace_back(item);
        EXPECT_EQ(clone.size(), q.Size());
    }
}

/**
* Dequeue()
*   Returns a node pointer or nullptr.
*/
TYPED_TEST_P(QueueTest, Dequeue) {
    using I              = TypeParam;
    using N              = BiDirectionalNode;
    using Node           = BiDirectionalNode<I>;
    std::vector<I>& keys = this->keys;
    Queue<N, I>& test_Q  = this->test_Q;


    // Ensure a call to Dequeue() from an empty Queue returns nullptr.
    Queue<N, I> q;
    Node* n = q.Dequeue();  // Releases allocated nodes.
    EXPECT_EQ(nullptr, n);
    
    // 1. Compare values of 'test_Q' with those of initialization vector 'keys.'
    Queue<N, I> cleanup_Q;  // Performs deallocation.
    for (I& item : keys) {
        n = test_Q.Dequeue();
        EXPECT_EQ(item, n->item);
        cleanup_Q.Enqueue(n);
    }
    
    // 2. Ensure 'test_Q' is empty.
    EXPECT_EQ(0, test_Q.Size());
 
    n = test_Q.Dequeue();
    EXPECT_EQ(nullptr, n);
    
    cleanup_Q.Enqueue(n);
}