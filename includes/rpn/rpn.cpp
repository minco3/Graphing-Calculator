#include "rpn.h"

RPN::RPN(const Queue<Token*>& input_q) {
    queue=input_q;
}

double RPN::operator() (double value) { // used for running the alg
    double answer;
    Queue<Token*> _o;
    Stack<double> _s;
    string _operator;
    double lhs, rhs;
    while(!queue.empty()) {
        //Token* op = queue.pop();
        switch(queue.front()->TypeOf()) {
            case INTEGER:
                _s.push(static_cast<Integer*>(queue.pop())->getValue()); // feels like theres a better way
                break;
            case OPERATOR:
                rhs = _s.pop();
                lhs = _s.pop();
                _operator = (static_cast<Operator*>(queue.pop())->getOperator());
                if (_operator == "+") {
                    _s.push(lhs + rhs);
                } else if (_operator == "-") {
                    _s.push(lhs - rhs);
                } else if (_operator == "*") {
                    _s.push(lhs*rhs);
                } else if (_operator == "/") {
                    _s.push(lhs/rhs);
                } else if (_operator == "^") {
                    _s.push(pow(lhs, rhs));
                }
                break;
            case FUNCTION:
                queue.pop();
                _s.push(value);
                break;
            default:
                break;
        }
    }

    return _s.top();
}

void RPN::set_input(const Queue<Token*> &input_q) {
    queue = input_q;
}
