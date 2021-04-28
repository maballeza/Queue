#pragma once

template<typename T>
struct Node{
    Node() : data(T{}), next(nullptr) {}
    ~Node() {}
    T data;
private:
    Node(T dat) : data(dat), next(nullptr) {}
    Node* next;
    template<typename T> friend class Queue;
};

template<typename T>
class Queue {
public:
    Queue() : tail(nullptr) { head = tail; }
    Queue(Queue&&) noexcept;
    Queue& operator=(Queue&&) noexcept;
    ~Queue();

    Node<T>* Enqueue(T&& obj); // Returns nullptr if allocation fails.
    T Dequeue();

private:
    Node<T>* Allocate(T&& obj) noexcept;
    void DeallocateList(Node<T>* n);
    
    Node<T>* head;  // Value-storing.
    Node<T>* tail;  // nullptr: The condition head == tail indicates an empty queue.
};

template<typename T>
Queue<T>::Queue(Queue&& q) noexcept : tail(nullptr) {
    if (Node<T>* n = q.head) {
        head = Allocate(std::forward<T>(n->data));
        if (n = n->next) {
            Node<T>* m = Allocate(std::forward<T>(n->data));
            head->next = m;
            while (n = n->next) {
                m->next = Allocate(std::forward<T>(n->data));
                m = m->next;
            }
            m->next = tail;
        }
        else {
            head->next = tail;
        }
        DeallocateList(q.head);
        q.head = nullptr;
    }
    else {
        head = tail;
    }
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& q) noexcept {
    if (Node<T>* n = q.head) {
        if (head != tail) {
            DeallocateList(head);
        }
        head = Allocate(std::forward<T>(n->data));
        if (n = n->next) {
            Node<T>* m = Allocate(std::forward<T>(n->data));
            head->next = m;
            while (n = n->next) {
                m->next = Allocate(std::forward<T>(n->data));
                m = m->next;
            }
            m->next = tail;
        }
        else {
            head->next = tail;
        }
        DeallocateList(q.head);
        q.head = nullptr;
    }
    else {
        head = tail;
    }
    return *this;
}

template<typename T>
inline Queue<T>::~Queue() {
    if (head != tail) { // Checks for an empty list.
        DeallocateList(head);
    }
}

template<typename T>
void Queue<T>::DeallocateList(Node<T>* n) {
    if (n->next != nullptr) {
        DeallocateList(n->next);
    }
    delete n;
}

template<typename T>
typename Node<T>* Queue<T>::Allocate(T&& obj) noexcept {
    try {
        return new Node<T>{ std::forward<T>(obj) };
    }
    catch (std::bad_alloc& e) {
        std::cerr << "Object allocation failure on line " << __LINE__ - 3 << " of " << __FILE__ << "." << std::endl;
        return nullptr;
    }
}

template<typename T>
Node<T>* Queue<T>::Enqueue(T&& obj) {
    Node<T>* n = Allocate(std::forward<T>(obj));
    if (n) {
        if (head == tail) { // Initialize the Queue.
            head = n;
            head->next = tail;
        }
        else if (head->next == tail) { // Inductive step.
            head->next = n;
        }
        else { // Search for the node preceding the tail.
            Node<T>* tailadj = head->next;
            while (tailadj->next != tail) {
                tailadj = tailadj->next;
            }
            tailadj->next = n;
        }
        n->next = tail;
    }
    return n;
}

template<typename T>
T Queue<T>::Dequeue() {
    if (Node<T>* temp = head) {
        Node<T> ret = *temp;
        if (head = head->next) {
            head->next = temp->next->next;
        }
        delete temp;
        return ret.data;
    }
    else {
        return T{ -1 };
    }
}