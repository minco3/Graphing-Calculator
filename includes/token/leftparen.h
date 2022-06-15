#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include "token.h"

class LeftParen : public Token {

    public:

    LeftParen();
    TOKEN_TYPES TypeOf() {return LPAREN;}
    void Print(ostream &outs) const {outs << "(";}

};

#endif //LEFTPAREN_H