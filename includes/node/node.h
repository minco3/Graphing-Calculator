#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
struct node
{
public:
    node(const T& item = T(), node<T>* next = nullptr) : _item(item), _next(next) {}

    template <typename U>
    friend ostream& operator << (ostream& outs, const node<U> &printMe);

    T _item;
    node<T>* _next;
};

template <typename T> ostream& operator << (ostream& outs, const node<T> &printMe) {
    assert(printMe);
    outs << '[' << printMe._item << "]-> ";
    return outs;
}

#endif // NODE_H