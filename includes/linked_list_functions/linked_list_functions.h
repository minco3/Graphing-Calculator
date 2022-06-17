#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <cassert>

#include "../node/node.h"

using namespace std;

// Declaration
//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T>* head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key);

template <typename T>
node<T>* _insert_head(node<T>* &head, T insert_this);

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>* &head, node<T>* after_this, T insert_this);

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>* &head, node<T>* before_this, T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>* &head, node<T>* delete_this);

//duplicate the list
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate list and return the last node of the copy
template <typename T>
node<T>* _copy_list(node<T>* &dest, node<T>* src);

//delete all the nodes
template <typename T>
void _clear_list(node<T>* &head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

//insert
template <typename T>
node<T>* _insert_sorted(node<T>* &head, T item, bool ascending=true);

//insert or add if a dup
template <typename T>
node<T>* _insert_sorted_and_add(node<T>* &head, T item, bool ascending=true);

//node after which this item goes order: 0 ascending
template <typename T>
node<T>* _where_this_goes(node<T>* head, T item, bool ascending=true);

//Last node in the list, never use this function.
template <typename T>
node<T>* _last_node(node<T>* head);




// Definition

template <typename T>
void _print_list(node<T>* head) {
    while (head != nullptr) {
        cout << *head << "->";
        head = head->_next;
    }
    cout << "|||" << endl;
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T>* head) {
    if (head != nullptr) {
        _print_list_backwards(head->_next);
        cout << *head << "->";
    }
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key) {
    while (head != nullptr) {
        if (head->_item==key) return head;
        else head = head->_next;
    }
    return nullptr;
}

template <typename T>
node<T>* _insert_head(node<T>* &head, T insert_this) {
    head = new node<T>(insert_this, head);
    return head;
}

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>* &head, node<T>* after_this, T insert_this) {
    node<T>* current = head;

    if (head==nullptr||after_this == nullptr)
        return _insert_head(head, insert_this);


    //assert(_search_list(head, after_this->_item) != nullptr);             idk why this is causing issues
    after_this->_next = new node<T>(insert_this, after_this->_next);

    // return head;
    return after_this->_next;
}

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>* &head, node<T>* before_this, T insert_this) {
    node<T>* current = head;
    node<T>* previous = _previous_node(head, before_this);

    if (head==nullptr||previous==nullptr)
        return _insert_head(head, insert_this);

    assert(_search_list(head, before_this->_item) != nullptr);
    previous->_next = new node<T>(insert_this, before_this);

    return previous->_next;
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this) {
    if (head == nullptr) return nullptr;
    while (head->_next != nullptr && head->_next != prev_to_this)
            head = head->_next;

    return head->_next == prev_to_this ? head : nullptr;

}

//delete, return item
template <typename T>
T _delete_node(node<T>* &head, node<T>* delete_this) {
    T deleted = delete_this->_item;

    if (head == delete_this) {
        head = delete_this->_next;
    } else {
        node<T>* previous = _previous_node(head, delete_this);
        
        if (previous==nullptr) return T();

        previous->_next = delete_this->_next;
    }
    
    delete delete_this;

    return deleted;

}

//duplicate the list
template <typename T>
node<T>* _copy_list(node<T>* head) {
    node<T>* dest;

    _copy_list(dest, head);

    return dest;
}

//duplicate list and return the last node of the copy
template <typename T>
node<T>* _copy_list(node<T>* &dest, node<T>* src) {
    node<T>* temp = nullptr;
    dest = nullptr;

    while (src != nullptr) {
        temp = _insert_after(dest, temp, src->_item);
        src = src->_next;
    }

    return temp;
}

//delete all the nodes
template <typename T>
void _clear_list(node<T>* &head) {
    
    while (head!=nullptr) {
        node<T>* temp = head->_next;
        delete head;
        head = temp;
    }    
    head = nullptr;
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos) {
    for (int i=0; i<pos; i++) {
        assert(head!=nullptr);
        head = head->_next;
    }
    return head->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

//insert
template <typename T>
node<T>* _insert_sorted(node<T>* &head, T item, bool ascending) {
    return _insert_after(head, _where_this_goes(head, item, ascending), item);
}

//insert or add if a dup
template <typename T>
node<T>* _insert_sorted_and_add(node<T>* &head, T item, bool ascending) {
    if (head == nullptr) return _insert_head(head, item);

    node<T>* pos = _where_this_goes(head, item, ascending);

    if (pos == nullptr) return _insert_head(head, item);

    if (pos->_item == item) {
        pos->_item *= 2;
        return pos;
    } else {
        return _insert_after(head, pos, item);
    }
}

//node after which this item goes order: 0 ascending
template <typename T>
node<T>* _where_this_goes(node<T>* head, T item, bool ascending) {
    if (head == nullptr) return head;
    if (ascending&&head->_item>item) return nullptr;
    if (!ascending&&head->_item<item) return nullptr;
    while(head->_next!=nullptr) {
        if (ascending) {
            if (head->_next->_item>item&&head->_item<=item) {
                return head;
            }
        } else {
            if (head->_next->_item<item&&head->_item>=item) {
                return head;
            }
        }
        head = head->_next;
    }
    return head;
}

//Last node in the list, never use this function.
template <typename T>
node<T>* _last_node(node<T>* head) {
    while(head->_next != nullptr) {
        head = head->_next;
    }
    return head;
}


// TODO



#endif // LINKED_LIST_FUNCTIONS_H