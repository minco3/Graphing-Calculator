#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H

#include "token.h"

class RightParen : public Token {

    public:

    RightParen();
    TOKEN_TYPES TypeOf() {return RPAREN;}
    void Print(ostream &outs) const {outs << ")";}
};

#endif //RIGHTPAREN_H