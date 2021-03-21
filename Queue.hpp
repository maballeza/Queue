#pragma once

template<typename T>
class Queue
{
public:
    /**
     * The condition 'head' == 'tail' is used to signal an empty queue.
     */
    Queue() : head(Allocate()), tail(head) {}
    ~Queue();

    void Enqueue(T&& obj);
    T* Dequeue();

private:
    struct Node
    {
        Node() : data(nullptr), next(nullptr) {}
        Node(T* dat) : data(dat), next(nullptr) {}
        Node(Node* N) : data(N->data), next(N->next) {}
        ~Node() { if (data) Deallocate(data); next = nullptr; }
        T* data;
        Node* next;
    };

    Node* Allocate(T* obj = nullptr) noexcept;
    static void Deallocate(T* obj) noexcept;
    static void Deallocate(Node* n) noexcept;
    
    Node* head;  // Value-storing, initialized as nullptr
    Node* tail;  // Always nullptr
};

template<typename T>
inline Queue<T>::~Queue()
{
    if (tail != head)
        Deallocate(tail);
    Deallocate(head);
}

template<typename T>
inline void Queue<T>::Enqueue(T&& obj) {
    if (head == tail) {
        Deallocate(head);
        head = Allocate(&obj);
        tail = Allocate();
        head->next = tail;
        return;
    }
    Node* adj = head;
    while (adj->next != tail) {
        adj = adj->next;
    }
    adj->next = Allocate(&obj);
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
    Deallocate(temp);
    
    return &ret;
}

template<typename T>
typename Queue<T>::Node* Queue<T>::Allocate(T* obj) noexcept {
    try {
        if (obj != nullptr) 
            obj = new T{ *obj };
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl
                  << "Object allocation failure." << std::endl;
    }

    try {
        Node* ret = new Node{ obj };
        return ret;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl
                  << "Node allocation failure." << std::endl;
    }
}

template<typename T>
void Queue<T>::Deallocate(T* obj) noexcept {
    try {
        delete obj;
        obj = nullptr;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl
                  << "Object deallocation failure." << std::endl;
    }
}

template<typename T>
void Queue<T>::Deallocate(Node* n) noexcept {
    try {
        delete n;
        n = nullptr;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl
                  << "Node deallocation failure." << std::endl;
    }
}