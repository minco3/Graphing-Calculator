#include "function.h"

    Function::Function() {
        _function = "";
    }
    Function::Function(const Function& other) {
        _function = other._function;
    }
    Function& Function::operator=(const Function& RHS) {
        _function = RHS._function;
        return *this;
    }