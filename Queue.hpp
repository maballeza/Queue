#pragma once
#include "Node.hpp"

//#define BUILD
template<class I>
class Queue {
public:
    using Node = DirectedNode<I>;
    using Node = DirectedNode<I>;

    Queue() : head{}, tail{}, size{} {}
    Queue(Queue&&) noexcept;
    ~Queue();

#ifdef BUILD
#ifdef HANDLE
    void Enqueue(Node* n);
    HNode<Node> Dequeue();
#else
    void Enqueue(Node* n);
    Node* Dequeue();
#endif
#else
#ifdef HANDLE
    void Enqueue(I&& itm);
    HNode<Node> Dequeue();
#else
    void Enqueue(I&& itm);
    Node Dequeue();
#endif
#endif
    int Size() const { return size; }

private:
    void DeallocateQueue(Node** n);
    
    Node* head;  // Value-storing.
    Node* tail;  // The condition head == tail indicates an empty queue.
    int size;
};

template<class I>
Queue<I>::Queue(Queue&& q) noexcept : head{ q.head }, tail {}, size(q.size) {
    q.head = nullptr;
    q.size = 0;
}

template<class I>
Queue<I>::~Queue() {
    if (head != tail) {
        DeallocateQueue(&head);
    }
    size = 0;
}

#ifdef BUILD
template<class I>
void Queue<I>::Enqueue(Node* n) {
    if (n) {
        if (head == tail) { // Initialize the Queue.
            head = n;
            head->next = tail;
        }
        else if (head->next == tail) { // Inductive step.
            head->next = n;
        }
        else { // Search for the node preceding the tail.
            Node* m = head->next;
            while (m->next != tail) {
                m = m->next;
            }
            m->next = n;
        }
        n->next = tail;
        ++size;
    }
}
#ifdef HANDLE
template<class I>
HNode<typename Queue<I>::Node> Queue<I>::Dequeue() {
    if (Node* temp = head) {
        if (head = head->next) {
            head->next = temp->next->next;
        }
        --size;
        return HNode{ temp };
    }
    else {
        return HNode{ temp };
    }
}

template<>
inline HNode<typename Queue<std::string>::Node> Queue<std::string>::Dequeue() {
    if (Node* temp = head) {
        if (head = head->next) {
            head->next = temp->next->next;
        }
        --size;
        return HNode{ temp };
    }
    else {
        return HNode{ temp };
    }
}
#else
template<class I>
typename Queue<I>::Node* Queue<I>::Dequeue() {
    if (Node* temp = head) {
        if (head = head->next) {
            head->next = temp->next->next;
        }
        Node ret{ std::move(*temp) };
        delete temp;
        --size;
        return temp{ ret };
    }
    else {
        return temp;
    }
}

template<>
inline typename Queue<std::string>::Node* Queue<std::string>::Dequeue() {
    if (Node* temp = head) {
        if (head = head->next) {
            head->next = temp->next->next;
        }
        Node ret{ std::move(*temp) };
        delete temp;
        --size;
        return temp{ ret };
    }
    else {
        return temp;
    }
}
#endif
#endif

#ifndef BUILD
template<class I>
void Queue<I>::Enqueue(I&& itm) {
    if (Node* n = Node::Build(std::forward<I>(itm))) {
        if (head == tail) { // Initialize the Queue.
            head = n;
            head->next = tail;
        }
        else if (head->next == tail) { // Inductive step.
            head->next = n;
        }
        else { // Search for the node preceding the tail.
            Node* m = head->next;
            while (m->next != tail) {
                m = m->next;
            }
            m->next = n;
        }
        n->next = tail;
        ++size;
    }
}

#ifdef HANDLE
template<class I>
HNode<typename Queue<I>::Node> Queue<I>::Dequeue() {
    if (Node* temp = head) {
        if (head = head->next) {
            head->next = temp->next->next;
        }
        --size;
        return HNode{ temp };
    }
    else {
        return HNode<typename Queue<I>::Node>{};
    }
}

template<>
inline HNode<typename Queue<std::string>::Node> Queue<std::string>::Dequeue() {
    if (Node* temp = head) {
        if (head = head->next) {
            head->next = temp->next->next;
        }
        --size;
        return HNode{ temp };
    }
    else {
        return HNode<typename Queue<std::string>::Node>{};
    }
}
#else
template<class I>
typename Queue<I>::Node Queue<I>::Dequeue() {
    if (Node* temp = head) {
        if (head = head->next) {
            head->next = temp->next->next;
        }
        Node ret{ std::move(*temp) };
        delete temp;
        --size;
        return ret;
    }
    else {
        return Node{ -1 };
    }
}

template<>
inline typename Queue<std::string>::Node Queue<std::string>::Dequeue() {
    if (Node* temp = head) {
        if (head = head->next) {
            head->next = temp->next->next;
        }
        Node ret{ std::move(*temp) };
        delete temp;
        --size;
        return ret;
    }
    else {
        return Node{ "-1" };
    }
}
#endif
#endif

template<class I>
void Queue<I>::DeallocateQueue(Node** n) {
    if (Node* m = *n; m->next != nullptr) {
        DeallocateQueue(&m->next);
    }
    delete* n;
    *n = nullptr;
}