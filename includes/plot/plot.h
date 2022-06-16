#ifndef PLOT_H
#define PLOT_H

#include "../point/point.h"

#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"

#include "../queue/MyQueue.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

Queue<Point> PlotExpression(string expression, double low, double high, double increments) {
    Queue<Point> points;
    Queue<Token*> postfix;
    postfix.push(new Integer(1));
    postfix.push(new Function("X"));
    postfix.push(new Operator("+"));
    RPN rpn(postfix);
    for (float i=low; i<=high; i+=increments) {
        float y = rpn(i);
        points.push(Point(i,y));
        std::cout << Point(i,y).x() << std::endl;
        std::cout << Point(i,y).getVector().x << std::endl;
    }
    return points;
}

#endif // PLOT_H