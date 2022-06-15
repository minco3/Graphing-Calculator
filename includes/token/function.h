#ifndef FUNCTION_H
#define FUNCTION_H

#include "token.h"

#include <string>

class Function : public Token {

    public:
    Function();
    Function(const Function& other);
    Function(string str) : _function(str) {}
    Function& operator =(const Function& RHS);
    TOKEN_TYPES TypeOf() {return FUNCTION;}
    void Print(ostream &outs) const {outs << _function;}
    string getFunction() {return _function;}

    private:
    string _function;
    
};


#endif // FUNCTION_H