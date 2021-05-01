#pragma once

template<typename T>
struct Node{
    T item;
private:
    template<typename T> friend class Queue;
    Node(T itm) : item(itm), next{} {}
    Node(Node&& n) :
        item(n.item), next(n.next) { n.item = T{}; n.next = nullptr; }
    Node* next;
};

/**
* The condition head == tail indicates an empty queue.
*/
template<typename T>
class Queue {
public:
    Queue() : head{}, tail{} {}
    Queue(Queue&&) noexcept;
    ~Queue();

    void Enqueue(T&& itm); // Returns nullptr if allocation fails.
    Node<T> Dequeue();

private:
    Node<T>* Allocate(T&& itm) noexcept;
    void DeallocateList(Node<T>** n);
    
    Node<T>* head;  // Value-storing.
    Node<T>* tail;
};

template<typename T>
Queue<T>::Queue(Queue&& q) noexcept : tail{} {
    if (Node<T>* n = q.head) {
        head = Allocate(std::forward<T>(n->item));
        if (n = n->next) {
            Node<T>* m = Allocate(std::forward<T>(n->item));
            head->next = m;
            while (n = n->next) {
                m->next = Allocate(std::forward<T>(n->item));
                m = m->next;
            }
            m->next = tail;
        }
        else {
            head->next = tail;
        }
        DeallocateList(&q.head);
    }
    else {
        head = tail;
    }
}

template<typename T>
Queue<T>::~Queue() {
    if (head != tail) {
        DeallocateList(&head);
    }
}

template<typename T>
void Queue<T>::DeallocateList(Node<T>** n) {
    if ((*n)->next != nullptr) {
        DeallocateList(&(*n)->next);
    }
    delete *n;
    *n = nullptr;
}

template<typename T>
Node<T>* Queue<T>::Allocate(T&& itm) noexcept {
    try {
        return new Node<T>{ std::forward<T>(itm) };
    }
    catch (std::bad_alloc& e) {
        std::cerr << "Node allocation failure on line " << __LINE__ - 3 << " of " << __FILE__ << "." << std::endl;
        return nullptr;
    }
}

template<typename T>
void Queue<T>::Enqueue(T&& itm) {
    if (Node<T>* n = Allocate(std::forward<T>(itm))) {
        if (head == tail) { // Initialize the Queue.
            head = n;
            head->next = tail;
        }
        else if (head->next == tail) { // Inductive step.
            head->next = n;
        }
        else { // Search for the node preceding the tail.
            Node<T>* m = head->next;
            while (m->next != tail) {
                m = m->next;
            }
            m->next = n;
        }
        n->next = tail;
    }
}

template<typename T>
Node<T> Queue<T>::Dequeue() {
    if (Node<T>* temp = head) {
        if (head = head->next) {
            head->next = temp->next->next;
        }
        Node<T> ret{ std::move(*temp) };
        delete temp;
        return ret;
    }
    else {
        return Node<T>{ -1 };
    }
}