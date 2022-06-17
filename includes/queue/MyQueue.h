#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <iomanip>

#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Queue
{
public:
  class Iterator
  {
  public:
    //Give access to list to access _ptr
    friend class Queue;

    //default ctor
    Iterator(){_ptr = nullptr;}
    //Point Iterator to where p is pointing to
    Iterator(node<T>* p):_ptr(p){}

    //dereference operator
    T& operator *(){assert(_ptr); return _ptr->_item;}
    //member access operator
    T* operator ->(){assert(_ptr); return &_ptr->_item;}
    //true if _ptr is NULL
    bool is_null(){return _ptr == nullptr;}

    //true if left != right
    friend bool operator !=(const Iterator &left, const Iterator &right){return !(left==right);}
    //true if left == right
    friend bool operator ==(const Iterator &left, const Iterator &right){return left._ptr==right._ptr;}
    //member operator:  ++it; or ++it = new_value
    Iterator& operator ++(){ _ptr = _ptr->_next; return *this;}
    //friend operator: it++
    friend Iterator operator ++(Iterator &it, int unused){it._ptr = it._ptr->_next; return it;}
  private:
    node<T>* _ptr; //pointer being encapsulated
  };

  //CTOR
  Queue();

  //BIG 3:
  Queue(const Queue<T>& copyMe);
  ~Queue();
  Queue<T>& operator =(const Queue<T>& RHS);

  //Operations:
  void push(T item);
  T pop();

  //Accessors:
  Iterator begin() const;             //Iterator to the head node
  Iterator end() const;               //Iterator to the last node

  //Checkers:
  int size() const { return _size; }
  bool empty() { return _front==nullptr; }
  T front() { return _front->_item; }
  T back() { return _rear->_item; }
  
  void print_pointers();
  
  template<typename TT>
  friend ostream& operator <<(ostream& outs, const Queue<TT>& printMe);
  
private:
  node<T>* _front;
  node<T>* _rear;
  int _size;
};


//Definition

  //CTOR
template <typename T>  Queue<T>::Queue() {
  _front = nullptr;
  _rear = nullptr;
  _size = 0;
}

  //BIG 3:
template <typename T>  Queue<T>::Queue(const Queue<T>& copyMe) {
  _front = _copy_list(copyMe._front);
  _rear = _last_node(_front);
  _size = copyMe._size;
}
template <typename T>  Queue<T>::~Queue() {
  _clear_list(_front);
}
template <typename T>  Queue<T>& Queue<T>::operator =(const Queue<T>& RHS) {
  _front = _copy_list(RHS._front);
  _rear = _last_node(_front);
  _size = RHS._size;
  return *this;
}

  //Operations:
template <typename T>  void Queue<T>::push(T item) {
  _size++;
  _rear = _insert_after(_front, _rear, item);
}
template <typename T>  T Queue<T>::pop() {
  if (!empty()) {
  _size--;
  return _delete_node(_front, _front);
  } else return T();
}

  //Accessors:
template <typename T>  typename Queue<T>::Iterator Queue<T>::begin() const {             //Iterator to the head node
  return Iterator(_front);
}
template <typename T>  typename Queue<T>::Iterator Queue<T>::end() const{               //Iterator to NULL
  return Iterator(_rear->_next);
}
  
template <typename T>  void Queue<T>::print_pointers() {
  // what is this
}
  
template<typename TT> ostream& operator <<(ostream& outs, const Queue<TT>& printMe) {
  if (printMe._front==nullptr) return outs;
  for (typename Queue<TT>::Iterator it = printMe.begin(); it != printMe.end(); it++) {
  outs << '[' << *it << "]-> ";
  }
  outs << "|||" << endl;
  return outs;
}


//TODO

#endif //MYQUEUE_H