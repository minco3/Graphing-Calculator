#include "integer.h"

Integer::Integer() {
    value = 0;
}
Integer::Integer(const Integer& other) {
    value = other.value;
}
Integer& Integer::operator = (const Integer& RHS) {
    value = RHS.value;
    return *this;
}