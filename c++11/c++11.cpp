#include <iostream>
#include <stdexcept>

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class Queue {
private:
    Node* front;
    Node* rear;
    size_t size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T value) {
        Node* newNode = new Node(value);
        if (rear) {
            rear->next = newNode;
            newNode->prev = rear;
        }
        rear = newNode;
        if (!front) {
            front = rear;
        }
        ++size;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        T value = front->data;
        Node* temp = front;
        front = front->next;
        if (front) {
            front->prev = nullptr;
        }
        else {
            rear = nullptr;
        }
        delete temp;
        --size;
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return front->data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

    Node* cloneHelper(Node* node) const {
        if (!node) return nullptr;
        Node* newHead = new Node(node->data);
        Node* current = newHead;
        Node* original = node->next;
        while (original) {
            Node* newNode = new Node(original->data);
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
            original = original->next;
        }
        return newHead;
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
        }
        else {
            head = newNode;
        }
        tail = newNode;
    }

    void display() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "NULL" << std::endl;
    }

    DoublyLinkedList clone() const {
        DoublyLinkedList newList;
        newList.head = cloneHelper(head);
        Node* current = newList.head;
        while (current && current->next) {
            current = current->next;
        }
        newList.tail = current;
        return newList;
    }

    DoublyLinkedList operator+(const DoublyLinkedList& other) const {
        DoublyLinkedList result;
        Node* current = head;
        while (current) {
            result.append(current->data);
            current = current->next;
        }
        current = other.head;
        while (current) {
            result.append(current->data);
            current = current->next;
        }
        return result;
    }

    DoublyLinkedList operator*(const DoublyLinkedList& other) const {
        DoublyLinkedList result;
        Node* current1 = head;
        while (current1) {
            Node* current2 = other.head;
            while (current2) {
                if (current1->data == current2->data) {
                    result.append(current1->data);
                    break;
                }
                current2 = current2->next;
            }
            current1 = current1->next;
        }
        return result;
    }
};

template <typename T>
class Array {
private:
    DoublyLinkedList list;
    size_t size;
    size_t grow;

public:
    Array() : size(0), grow(1) {}

    size_t GetSize() const {
        return size;
    }

    void SetSize(int newSize, int newGrow = 1) {
        grow = newGrow;
        while (size < newSize) {
            list.append(0);
            ++size;
        }
        while (size > newSize) {
            list.removeAt(size - 1);
            --size;
        }
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
    }

    void RemoveAll() {
        list = DoublyLinkedList();
        size = 0;
    }

    T& GetAt(size_t index) {
    }

    void SetAt(size_t index, const T& value) {
    }

    void Add(const T& value) {
        list.append(value);
        ++size;
    }

    void Append(const Array<T>& other) {
    }

    T* GetData() {
    }

    void InsertAt(size_t index, const T& value) {
    }

    void RemoveAt(size_t index) {
    }
};

int main() {
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    std::cout << "Front of queue: " << queue.peek() << std::endl;
    queue.dequeue();
    std::cout << "New front of queue: " << queue.peek() << std::endl;

    DoublyLinkedList list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);

    DoublyLinkedList list2;
    list2.append(3);
    list2.append(4);
    list2.append(5);

    DoublyLinkedList mergedList = list1 + list2;
    std::cout << "Merged list: ";
    mergedList.display();

    DoublyLinkedList commonList = list1 * list2;
    std::cout << "Common elements: ";
    commonList.display();

    return 0;
}
