#pragma once
#include "Node.hpp"

template<class I>
class Queue {
public:
    using Node = DirectedNode<I>;

    Queue() : head{}, tail{}, size{} {}
    Queue(Queue&&) noexcept;
    ~Queue();

    void Enqueue(I&& itm);
    Node Dequeue();
    int Size() const { return size; }

private:
    Node* Allocate(I&& itm) noexcept;
    void DeallocateQueue(Node** n);
    
    Node* head;  // Value-storing.
    Node* tail;  // The condition head == tail indicates an empty queue.
    int size;
};

template<class I>
Queue<I>::Queue(Queue&& q) noexcept : tail{}, size(q.size) {
    if (Node* n = q.head) {
        head = Allocate(std::forward<I>(n->item));
        if (n = n->next) {
            Node* m = Allocate(std::forward<I>(n->item));
            head->next = m;
            while (n = n->next) {
                m->next = Allocate(std::forward<I>(n->item));
                m = m->next;
            }
            m->next = tail;
        }
        else {
            head->next = tail;
        }
        DeallocateQueue(&q.head);
    }
    else {
        head = tail;
    }
    q.size = 0;
}

template<class I>
Queue<I>::~Queue() {
    if (head != tail) {
        DeallocateQueue(&head);
    }
    size = 0;
}

template<class I>
void Queue<I>::Enqueue(I&& itm) {
    if (Node* n = Allocate(std::forward<I>(itm))) {
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
       return Node{"-1"};
    }
}

template<class I>
typename Queue<I>::Node* Queue<I>::Allocate(I&& itm) noexcept {
    try {
        return new Node{ std::forward<I>(itm) };
    }
    catch (std::bad_alloc& /*e*/) {
        std::cerr << "Node allocation failure on line " << __LINE__ - 3 << " of " << __FILE__ << "." << std::endl;
        return nullptr;
    }
}

template<class I>
void Queue<I>::DeallocateQueue(Node** n) {
    if (Node* m = *n; m->next != nullptr) {
        DeallocateQueue(&m->next);
    }
    delete* n;
    *n = nullptr;
}