#pragma once

template<typename T>
class Queue {
public:
    struct Node {
        T item;
    private:
        friend class Queue;
        Node(T itm) : item(itm), next{} {}
        Node(Node&& n) noexcept : item(n.item), next(n.next) {
            n.item = T{}; n.next = nullptr;
        }
        Node* next;
    };

    Queue() : head{}, tail{}, size{} {}
    Queue(Queue&&) noexcept;
    ~Queue();

    void Enqueue(T&& itm);
    Node Dequeue();
    int Size() const { return size; }

private:
    Node* Allocate(T&& itm) noexcept;
    void DeallocateQueue(Node** n);
    
    Node* head;  // Value-storing.
    Node* tail;  // The condition head == tail indicates an empty queue.
    int size;
};

template<typename T>
Queue<T>::Queue(Queue&& q) noexcept : tail{}, size(q.size) {
    if (Node* n = q.head) {
        head = Allocate(std::forward<T>(n->item));
        if (n = n->next) {
            Node* m = Allocate(std::forward<T>(n->item));
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
        DeallocateQueue(&q.head);
    }
    else {
        head = tail;
    }
    q.size = 0;
}

template<typename T>
Queue<T>::~Queue() {
    if (head != tail) {
        DeallocateQueue(&head);
    }
    size = 0;
}

template<typename T>
void Queue<T>::Enqueue(T&& itm) {
    if (Node* n = Allocate(std::forward<T>(itm))) {
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

template<typename T>
typename Queue<T>::Node Queue<T>::Dequeue() {
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

template<typename T>
typename Queue<T>::Node* Queue<T>::Allocate(T&& itm) noexcept {
    try {
        return new Node{ std::forward<T>(itm) };
    }
    catch (std::bad_alloc& /*e*/) {
        std::cerr << "Node allocation failure on line " << __LINE__ - 3 << " of " << __FILE__ << "." << std::endl;
        return nullptr;
    }
}

template<typename T>
void Queue<T>::DeallocateQueue(Node** n) {
    if (Node* m = *n; m->next != nullptr) {
        DeallocateQueue(&m->next);
    }
    delete* n;
    *n = nullptr;
}