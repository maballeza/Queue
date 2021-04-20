#pragma once

template<typename T>
class Queue
{
public:
    /**
     * The condition 'head' == 'tail' is used to signal an empty queue.
     */
    Queue() : tail(nullptr) { head = tail; }
    ~Queue();

    T* Enqueue(T&& obj);
    T Dequeue();

private:
    struct Node
    {
        Node(T dat) : data(dat), next(nullptr) {}
        ~Node() {}
        T data;
        Node* next;
    };

    Node* Allocate(T&& obj) noexcept;
    void DeallocateList(Node* n);
    
    Node* head;  // Value-storing, initialized as nullptr
    Node* tail;  // Always nullptr
};

template<typename T>
inline Queue<T>::~Queue() {
    if (head != tail) { // Checks for an empty list.
        DeallocateList(head);
    }
}

template<typename T>
typename Queue<T>::Node* Queue<T>::Allocate(T&& obj) noexcept {
    try {
        Node* ret = new Node{ std::move(obj) };
        return ret;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl
                  << "Object allocation failure." << std::endl;
        return nullptr;
    }
}

template<typename T>
void Queue<T>::DeallocateList(Node* n) {
    if (n->next != nullptr) {
        DeallocateList(n->next);
    }
    delete n;
}

template<typename T>
T* Queue<T>::Enqueue(T&& obj) {
    Node* adj = Allocate(std::move(obj));
    if (adj) {
        if (!head) { // Queue initialization: tail == nullptr.
            head = adj;
            head->next = tail;
            return &head->data;
        }
        else if (Node* found = head->next) { // Search for the node preceding the tail.
            while (found->next != tail) {
                found = found->next;
            }
            found->next = adj;
        }
        else { // Inductive step.
            head->next = adj;
        }
        adj->next = tail;
        return &adj->data;
    }
    else {
        return nullptr;
    }
}

template<typename T>
T Queue<T>::Dequeue() {
    if (head != tail) {
        T ret = head->data;
        Node* temp = head;
        if (head->next) {
            head = temp->next;
            head->next = temp->next->next;
        }
        else {
            head = tail;
        }
        delete temp;    // Assigning nullptr to temp->next is unnecessary in this context.
        return std::move(ret);
    }
}