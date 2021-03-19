#pragma once

template<typename T>
class Queue
{
public:
    /**
     * The condition 'head' == 'tail' is used to signal an empty queue.
     */
    Queue() : head(new Node), tail(head) {}
    ~Queue();

    void Enqueue(T&& obj);
    T* Dequeue();

private:
    struct Node
    {
        Node() : data(nullptr), next(nullptr) {}
        Node(T* dat) : data(new T(*dat)), next(nullptr) {}
        Node(Node* N) : data(N->data), next(N->next) { this = N; }
        ~Node() { delete data; data = nullptr; next = nullptr; }
        T* data;
        Node* next;
    };

    Node* head;  // Initialized as nullptr, stores values
    Node* tail;  // Always nullptr
};

template<typename T>
inline Queue<T>::~Queue()
{
    if (tail != head)
        delete tail;
    delete head;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
inline void Queue<T>::Enqueue(T&& obj) {
    if (head == tail) {
        tail = new Node;
        head->data = new T{ obj };
        head->next = tail;
        return;
    }
    Node* adj = head;
    while (adj->next != tail) {
        adj = adj->next;
    }
    adj->next = new Node{ &obj };
    adj->next->next = tail;
}

template<typename T>
inline T* Queue<T>::Dequeue() {
    if (head == tail)
        return nullptr;
    T ret = *head->data;
    Node* temp = head;
    head = temp->next;
    head->next = temp->next->next;
    delete temp;
    
    return &ret;
}