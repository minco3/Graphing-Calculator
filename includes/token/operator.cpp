#include "operator.h"

    Operator::Operator() {
        _operator = "";
    }
    Operator::Operator(const Operator& other) {
        _operator = other._operator;
    }
    Operator& Operator::operator =(const Operator& RHS) {
        _operator = RHS._operator;
        return *this;
    }

    int Operator::getOrder() {
        if (_operator == "+" || _operator == "-") {
            return 1;
        } else if (_operator == "*" || _operator == "/") {
            return 2;
        } else if (_operator == "^") {
            return 3;
        } else return 0;
    }