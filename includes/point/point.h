#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>

class Point {
    public:
    Point(float x, float y) : _x(x), _y(y) {}
    float x() {return _x;}
    float y() {return _y;}
    sf::Vector2f getVector();

    bool operator==(Point& right);

    private:
    float _x;
    float _y;
};

sf::Vector2f Point::getVector() {
    return sf::Vector2f(_x, _y);
}

bool Point::operator == (Point& right) {
    return _x == right._x&& _y==right._y;
}

#endif //POINT_H