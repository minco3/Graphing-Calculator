#ifndef OPERATOR_H
#define OPERATOR_H

#include "token.h"
#include <string>

class Operator : public Token {

    public:
    Operator();
    Operator(const Operator& other);
    Operator(string str) : _operator(str) {}
    Operator& operator =(const Operator& RHS);
    TOKEN_TYPES TypeOf() {return OPERATOR;}
    string getOperator(){return _operator;}
    int getOrder();
    void Print(ostream &outs) const {outs << _operator;}
    private:
    string _operator;
};


#endif // OPERATOR_H