#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

#include "constants.h"

using namespace std;

class Token {
    public:
    // return token type
    virtual TOKEN_TYPES TypeOf() {return TOKEN;}

    virtual void Print(ostream &outs) const;

    friend ostream& operator <<(ostream& outs, const Token* token);
    
    friend ostream &operator<<(ostream &outs, const Token &token);

};

#endif // TOKEN_H