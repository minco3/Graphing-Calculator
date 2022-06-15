#ifndef INTEGER_H
#define INTEGER_H

#include "token.h"

class Integer : public Token {
    public:

    Integer();
    Integer(const Integer& other);
    Integer(double num) : value(num) {}
    Integer& operator = (const Integer& RHS);
    double getValue() {return value;}
    TOKEN_TYPES TypeOf() {return INTEGER;}
    void Print(ostream &outs) const {outs << value;}
    private:
    double value;
};

#endif // INTEGER_H