#pragma once
#include "Node.hpp"

//#define BUILD
template<class I>
class Queue {
public:
    using Node = DirectedNode<I>;

    Queue() : head{}, tail{}, size{} {}
    Queue(Queue&&) noexcept;
    ~Queue();

#ifdef BUILD
    void Enqueue(Node* n);
    Node* Dequeue();
#endif
#ifndef BUILD
    void Enqueue(I&& itm);
    Node Dequeue();
#endif
    int Size() const { return size; }

private:
    void DeallocateQueue(Node** n);
    
    Node* head;  // Value-storing.
    Node* tail;  // The condition head == tail indicates an empty queue.
    int size;
};

template<class I>
Queue<I>::Queue(Queue&& q) noexcept : tail{}, size(q.size) {
    if (Node* n = q.head) {
        head = Node::Build(std::forward<I>(n->item));
        if (n = n->next) {
            Node* m = Node::Build(std::forward<I>(n->item));
            head->next = m;
            Node* l = n;
            while (n = n->next) {
                m->next = Node::Build(std::forward<I>(n->item));
                m = m->next;
                delete l;
                l = n;
            }
            m->next = tail;
            delete l;
        }
        else {
            head->next = tail;
        }
        Node** l = &q.head;
        delete* l;
        *l = nullptr;
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

template<class I>
void Queue<I>::DeallocateQueue(Node** n) {
    if (Node* m = *n; m->next != nullptr) {
        DeallocateQueue(&m->next);
    }
    delete* n;
    *n = nullptr;
}