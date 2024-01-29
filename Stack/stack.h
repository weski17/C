#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <cassert>

template<typename T, size_t I>
class Stack {
public:
    using vtype = T;

    Stack();
    ~Stack() {} // Leerer Destruktor
    Stack& operator=(const Stack& other);
    T pop();
    void push(const T&);
    bool isFull() const;
    bool isEmpty() const;
    size_t size() const;

private:
    T data[I];
    size_t currentSize;
};

template<typename T, size_t I>
Stack<T, I>::Stack() : currentSize(0) {}

template<typename T, size_t I>
T Stack<T, I>::pop() {
    assert(!isEmpty() && "Stack underflow");
    return data[--currentSize];
}

template<typename T, size_t I>
void Stack<T, I>::push(const T& element) {
    assert(!isFull() && "Stack overflow");
    data[currentSize++] = element;
}

template<typename T, size_t I>
bool Stack<T, I>::isEmpty() const {
    return currentSize == 0;
}

template<typename T, size_t I>
bool Stack<T, I>::isFull() const {
    return currentSize == I;
}

template<typename T, size_t I>
size_t Stack<T, I>::size() const {
    return currentSize;
}

template<typename T, size_t I>
Stack<T, I>& Stack<T, I>::operator=(const Stack<T, I>& other) {
    if (this != &other) {
        currentSize = other.currentSize;
        for (size_t i = 0; i < currentSize; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

#endif // STACK_H
