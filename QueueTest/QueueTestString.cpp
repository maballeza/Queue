#include "QueueTestString.hpp"

/**
* Default Constructor
*   Constructs an empty Queue.
*/
TEST_F(QueueTestString, DefaultConstructor) {
    

    Queue<std::string> q;
    EXPECT_EQ(0, q.Size());
    EXPECT_EQ(std::string{ "-1" }, q.Dequeue().item);
}

/**
* Move Constructor
*   Copies values and dequeues the source Queue.
*/
TEST_F(QueueTestString, MoveConstructor) {
    

    // Ensure sizes match between the "move-from" and the "moved-to" Queues.
    int QSize = Q.Size();
    Queue<std::string> q{ std::forward<Queue<std::string>>(Q) };
    EXPECT_EQ(q.Size(), QSize);

    // Ensure "Dequeue-ing" is performed when the "moved-from" Queue is moved.
    EXPECT_EQ(0, Q.Size());

    // Check the "moved-to" Queue value-matches the values used to initialize 'Q.'
    for (auto& v : vals) {
        EXPECT_EQ(v, q.Dequeue().item);
    }
}


/**
* Size()
*   Returns the size of the Queue.
*/
TEST_F(QueueTestString, Size) {
    

    // Empty Queue.
    Queue<std::string> q;
    EXPECT_EQ(0, q.Size());

    // Non-Empty Queue.
    int arbitrary = 20;
    for (int v = 0; v < arbitrary; ++v) {
        q.Enqueue(std::move(std::to_string(v)));
    }
    EXPECT_EQ(arbitrary, q.Size());
}

/**
* Enqueue()
*   Moves values into the Queue by r-value reference.
*/
TEST_F(QueueTestString, Enqueue) {
    

    Queue<std::string> q;
    std::vector<std::string> clone;
    for (auto& v : vals) {
        q.Enqueue(std::forward<std::string>(v));
        clone.emplace_back(v);
        EXPECT_EQ(clone.size(), q.Size());
    }
}

/**
* Dequeue()
*   Returns a Queue node with a valid value or -1.
*/
TEST_F(QueueTestString, Dequeue) {
    

    // Ensure a call to Dequeue() from an empty Queue returns -1.
    Queue<std::string> q;
    EXPECT_EQ(std::string{ "-1" }, q.Dequeue().item);

    // 1. Compare values of Q with those of initialization vector 'vals.'
    for (auto& v : vals) {
        EXPECT_EQ(v, Q.Dequeue().item);
    }

    // 2. Ensure Q is empty.
    EXPECT_EQ(0, Q.Size());
    EXPECT_EQ(std::string{ "-1" }, Q.Dequeue().item);
}