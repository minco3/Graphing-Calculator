#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <Vector>

#include "../point/point.h"
#include "../str_to_infix/str_to_infix.h"

#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"


#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
#include "../token/constants.h"

class Expression {
    public:
    friend class Graph;
    Expression(std::string str);
    void setExpression(std::string str);
    bool isLinear() {return linear;}
    float getSlope() {return slope;}
    float getIntercept() {return intercept;}

    private:
    void setLinear();
    //void simplify();
    vector<Point> points;
    Queue<Token*> postfix;
    bool linear;
    float slope;
    float intercept;
};

Expression::Expression(std::string str) {
    setExpression(str);
}

void Expression::setExpression(std::string str) {
    Queue<Token*> infix = strToInfix(str);
    ShuntingYard sy(infix);
    postfix = sy.postfix();
    setLinear();
}

void Expression::setLinear() {
    linear = true;
    Queue<Token*> expression(postfix);
    while(!expression.empty()) {
        switch (expression.front()->TypeOf()) {
            case OPERATOR:
                if (static_cast<Operator*>(expression.pop())->getOperator()=="^")
                linear = false;
                break;
            case FUNCTION:
                if (static_cast<Function*>(expression.pop())->getFunction()!="X")
                    linear = false;
                break;
            default:
                expression.pop();
                break;
        }
    }
    if (linear) {
        RPN rpn(postfix);
        slope = rpn(2)-rpn(1);
        intercept = rpn(0);
    }
}

// void Expression::simplify() {
//     Queue<Token*> _input(postfix);
//     Stack<Token*> _s;
//     string _operator, _function;
//     Token* lhs, rhs;
//     while(!_input.empty()) {
//         switch(_input.front()->TypeOf()) {
//             case INTEGER:
//                 _s.push(_input.pop());
//                 break;
//             case OPERATOR:
//                 rhs = _s.pop();
//                 lhs = _s.pop();
//                 _operator = (static_cast<Operator*>(_input.pop())->getOperator());
//                 if (_operator == "+") {
//                     _s.push(lhs + rhs);
//                 } else if (_operator == "-") {
//                     _s.push(lhs - rhs);
//                 } else if (_operator == "*") {
//                     _s.push(lhs*rhs);
//                 } else if (_operator == "/") {
//                     _s.push(lhs/rhs);
//                 } else if (_operator == "^") {
//                     _s.push(pow(lhs, rhs));
//                 }
//                 break;
//             case FUNCTION:
//                 _function = static_cast<Function*>(_input.pop())->getFunction();
//                 if (_function == "X")
//                     _s.push(value);
//                 else if (_function == "sin")
//                     _s.push(sin(_s.pop()));
//                 else if (_function == "cos")
//                     _s.push(cos(_s.pop()));
//                 else if (_function == "tan")
//                     _s.push(tan(_s.pop()));
//                 break;
//             default:
//                 break;
//         }
// }

#endif // EXPRESSION_H