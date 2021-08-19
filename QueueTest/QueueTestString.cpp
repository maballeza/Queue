#include "QueueTestString.hpp"

/**
* Default Constructor
*   Constructs an empty queue.
*/
TEST_F(QueueTestString, DefaultConstructor) {
    using Node = N<string>;

    Queue<N, string> q;
    EXPECT_EQ(0, q.Size());

    Node* n = q.Dequeue();
    EXPECT_EQ(nullptr, n);
}

/**
* Move Constructor
*   Clones values and dequeues the source queue.
*/
TEST_F(QueueTestString, MoveConstructor) {
    using Node = N<string>;
    
    // Ensure sizes do not match between the "moved-from" and the "moved-to" queues.
    Queue<N, string> q{ std::move(test_Q) };
    EXPECT_NE(q.Size(), test_Q.Size());

    // Ensure "Dequeue-ing" is performed when the "moved-from" queue is moved.
    EXPECT_EQ(0, test_Q.Size());

    // Check the values used to initialize 'test_Q' and the "moved-to" queue's values match.
    Queue<N, string> cleanup_Q;
    for (string& item : keys) {
        Node* n = q.Dequeue();  // Releases allocated nodes.
        EXPECT_EQ(item, n->item);
        cleanup_Q.Enqueue(n);   // Performs deallocation.
    }
}


/**
* Size()
*   Returns the size of the queue.
*/
TEST_F(QueueTestString, Size) {
    // Empty queue.
    Queue<N, string> q;
    EXPECT_EQ(0, q.Size());

    // Non-empty queue.
    int arbitrary = 20;
    for (int item = 0; item < arbitrary; ++item) {
        HNode<N, string> n = Build<N, string>::Instance(std::move(std::to_string(item)));
        q.Enqueue(n.Release());
    }
    EXPECT_EQ(arbitrary, q.Size());
}

/**
* Enqueue()
*   Moves values into the queue.
*/
TEST_F(QueueTestString, Enqueue) {
    Queue<N, string> q;
    std::vector<string> clone;
    for (string& item : keys) {
        HNode<N, string> n = Build<N, string>::Instance(std::move(item));
        q.Enqueue(n.Release());
        clone.emplace_back(item);
        EXPECT_EQ(clone.size(), q.Size());
    }
}

/**
* Dequeue()
*   Returns a node pointer or nullptr.
*/
TEST_F(QueueTestString, Dequeue) {
    using Node = N<string>;
    
    // Ensure a call to Dequeue() from an empty queue returns nullptr.
    Queue<N, string> q;
    Node* n = q.Dequeue();  // Releases allocated nodes.
    EXPECT_EQ(nullptr, n);

    // 1. Compare values of 'test_Q' with those of initialization vector 'keys.'
    Queue<N, string> cleanup_Q;  // Performs deallocation.
    for (string& item : keys) {
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