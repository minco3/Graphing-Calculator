#include "rpn.h"

RPN::RPN(const Queue<Token*>& input_q) {
    queue=input_q;
}

double RPN::operator() (double value) { // used for running the alg
    double answer;
    Queue<Token*> _o, _input(queue);
    Stack<double> _s;
    string _operator, _function;
    double lhs, rhs;
    while(!_input.empty()) {
        //Token* op = queue.pop();
        switch(_input.front()->TypeOf()) {
            case INTEGER:
                _s.push(static_cast<Integer*>(_input.pop())->getValue()); // feels like theres a better way
                break;
            case OPERATOR:
                rhs = _s.pop();
                lhs = _s.pop();
                _operator = (static_cast<Operator*>(_input.pop())->getOperator());
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
                _function = static_cast<Function*>(_input.pop())->getFunction();
                if (_function == "X")
                    _s.push(value);
                else if (_function == "sin")
                    _s.push(sin(_s.pop()));
                else if (_function == "cos")
                    _s.push(cos(_s.pop()));
                else if (_function == "tan")
                    _s.push(tan(_s.pop()));
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
