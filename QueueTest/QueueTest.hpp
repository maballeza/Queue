#pragma once
#include "gtest/gtest.h"
#include "../Queue.hpp"

/**
* class QueueTest
*   A type parameterized test for the queue interface.
*/
template <typename I>
class QueueTest : public testing::Test {
public:
    using N      = BiDirectionalNode;
    using Queue  = Queue<N, I>;
    using Handle = HNode<N, I>;

    void SetUp() override {
        for (I& item : keys) { // Initialize test_Q.
            Handle n = Build<N, I>::Instance(std::move(item));
            test_Q.Enqueue(n.Release());
        }
    }

    Queue test_Q;
    std::vector<I> keys { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
};

TYPED_TEST_SUITE_P(QueueTest);

/**
* Default Constructor
*   Constructs an empty queue.
*/
TYPED_TEST_P(QueueTest, DefaultConstructor) {
    using I     = TypeParam;
    using N     = BiDirectionalNode;
    using Queue = Queue<N, I>;
    using Node  = BiDirectionalNode<I>;
    
    Queue q;
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
    using Queue          = Queue<N, I>;
    using Node           = BiDirectionalNode<I>;
    std::vector<I>& keys = this->keys;
    Queue& test_Q        = this->test_Q;

    // Ensure sizes do not match between the "moved-from" and the "moved-to" queues.
    Queue q { std::move(test_Q) };
    EXPECT_NE(q.Size(), test_Q.Size());
    
    // Ensure "Dequeue-ing" is performed when the "moved-from" queue is moved.
    EXPECT_EQ(0, test_Q.Size());
    
    // Check the values used to initialize 'test_Q' and the "moved-to" queue's values match.
    Queue cleanup_Q;
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
    using I      = TypeParam;
    using N      = BiDirectionalNode;
    using Queue  = Queue<N, I>;
    using Handle = HNode<N, I>;
    
    // Empty queue.
    Queue q;
    EXPECT_EQ(0, q.Size());
    
    // Non-empty queue.
    int arbitrary = 20;
    for (int item = 0; item < arbitrary; ++item) {
        Handle n = Build<N, I>::Instance(std::move(item));
        q.Enqueue(n.Release());
    }
    EXPECT_EQ(arbitrary, q.Size());
}

/**
* EnqueueNode
*   Adds nodes to the queue, taking ownership.
*/
TYPED_TEST_P(QueueTest, EnqueueNode) {
    using I              = TypeParam;
    using N              = BiDirectionalNode;
    using Queue          = Queue<N, I>;
    using Handle         = HNode<N, I>;
    std::vector<I>& keys = this->keys;
    
    Queue q;
    std::vector<I> clone;
    for (I& item : keys) {
        Handle n = Build<N, I>::Instance(std::move(item));
        q.Enqueue(n.Release());
        clone.emplace_back(item);
        EXPECT_EQ(clone.size(), q.Size());
    }
}

/**
* EnqueueItem
*   Moves values into the queue.
*/
TYPED_TEST_P(QueueTest, EnqueueItem) {
    using I              = TypeParam;
    using N              = BiDirectionalNode;
    using Queue          = Queue<N, I>;
    std::vector<I>& keys = this->keys;
    
    Queue q;
    std::vector<I> clone;
    for (I& item : keys) {
        q.Enqueue(std::move(item));
        clone.emplace_back(item);
        EXPECT_EQ(clone.size(), q.Size());
    }
}

/**
* Dequeue()
*   Returns nullptr or a node pointer, transferring ownership.
*/
TYPED_TEST_P(QueueTest, Dequeue) {
    using I              = TypeParam;
    using N              = BiDirectionalNode;
    using Queue          = Queue<N, I>;
    using Node           = BiDirectionalNode<I>;
    Queue& test_Q        = this->test_Q;
    std::vector<I>& keys = this->keys;


    // Ensure a call to Dequeue() from an empty Queue returns nullptr.
    Queue q;
    Node* n = q.Dequeue();  // Releases allocated nodes.
    EXPECT_EQ(nullptr, n);
    
    // 1. Compare values of 'test_Q' with those of initialization vector 'keys.'
    Queue cleanup_Q;  // Performs deallocation.
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