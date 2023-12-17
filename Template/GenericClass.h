#ifndef GENERICCLASS_H
#define GENERICCLASS_H

#include <iostream>


template <typename T>
class GenericClass {
public:
    explicit GenericClass(T initial);
    void setData(T newData);
    T getData() const;

private:
    T data;
};

template <typename T>
GenericClass<T>::GenericClass(T initial) : data(initial) {}

template <typename T>
void GenericClass<T>::setData(T newData) {
    data = newData;
}

template <typename T>
T GenericClass<T>::getData() const {
    return data;
}

#endif 
