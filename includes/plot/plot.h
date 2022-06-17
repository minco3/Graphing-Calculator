#ifndef PLOT_H
#define PLOT_H

#include <cmath>

#include "../point/point.h"

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

Queue<Point> PlotExpression(Queue<Token*> expression, double low, double high, double increments) {
    Queue<Point> points;
    RPN rpn(expression);
    for (float i=low; i<=high; i+=increments) {
        float y = rpn(i);
        points.push(Point(i,y));
    }
    return points;
}

float PlotLine(Queue<Token*> expression, double low, double high) {
    RPN rpn(expression);
    float y1 = rpn(low), y2 = rpn(high);
    return sqrt(pow((high-low),2)+pow((y2-y1),2));
}

#endif // PLOT_H