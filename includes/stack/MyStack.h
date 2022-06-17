#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>

#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack
{
public:
  class Iterator
  {
  public:
    //Give access to list to access _ptr
    friend class Stack;

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
    Iterator& operator ++(){ _ptr = _ptr->_next; return this;}
    //friend operator: it++
    friend Iterator operator ++(Iterator &it, int unused){it._ptr = it._ptr->_next; return it;}
  private:
    node<T>* _ptr; //pointer being encapsulated
  };

  //CTOR
  Stack();

  //BIG 3:
  Stack(const Stack<T>& copyMe);
  ~Stack();
  Stack<T>& operator =(const Stack<T>& RHS);

  //Operations:
  void push(T item);

  //Accessors:
  Iterator begin() const;            //Iterator to the head node
  Iterator end() const;              //Iterator to NULL

  //Checkers:
  int size() const;
  bool empty();
  T top();
  T pop();

  template<typename U>
  friend ostream& operator <<(ostream& outs, const Stack<U>& printMe);
  
private:
  node<T>* _top;
  int _size;
};

//Definition

//CTOR
template <typename T> Stack<T>::Stack() {
  _top = nullptr;
  _size = 0;
}

  //BIG 3:
template <typename T> Stack<T>::Stack(const Stack<T>& copyMe) {
  _top = _copy_list(copyMe._top);
  _size = copyMe._size;
}
template <typename T> Stack<T>::~Stack() {_clear_list(_top);}
template <typename T> Stack<T>& Stack<T>::operator =(const Stack<T>& RHS) {
  _top = _copy_list(RHS._top);
  _size = RHS._size;
  return *this;
}

  //Operations:
template <typename T> void Stack<T>::push(T item) {_size++; _insert_head(_top, item);}

  //Accessors:
template <typename T> typename Stack<T>::Iterator Stack<T>::begin() const {return Iterator(_top);}            //Iterator to the head node
template <typename T> typename Stack<T>::Iterator Stack<T>::end() const {return Iterator(_last_node(_top)->_next);}              //Iterator to NULL

  //Checkers:
template <typename T> int Stack<T>::size() const { return _size; }
template <typename T> bool Stack<T>::empty() { return _top == nullptr; }
template <typename T> T Stack<T>::top() { if (!empty()) {return _top->_item;} else return T(); }
template <typename T> T Stack<T>::pop() { if (!empty()) {_size--; return _delete_node(_top, begin()._ptr);} else return T();}

template<typename U> ostream& operator <<(ostream& outs, const Stack<U>& printMe) {
  if (printMe._top==nullptr) return outs;
  for (typename Stack<U>::Iterator it = printMe.begin(); it != printMe.end(); it++) {
    outs << '[' << *it << "]-> ";
    }
    outs << "|||" << endl;
    return outs;
}

//TODO

#endif // MYSTACK_H