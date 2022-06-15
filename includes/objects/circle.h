#ifndef CIRCLE_H
#define CIRCLE_H

const int LOWER_BOUND = 10, UPPER_BOUND = 20;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../random/random.h"

class Circle {

    public:
    Circle(int x=100, int y=100);

    void draw(sf::RenderWindow& window, sf::Time& elapsed);

    private:
    float circleSize;
    sf::CircleShape circle;
    sf::Vector2f vector;

};

Circle::Circle(int x, int y) {
    circleSize = random(LOWER_BOUND, UPPER_BOUND);
    circle = sf::CircleShape(circleSize);
    circle.setPosition(x,y);
    circle.setFillColor(sf::Color(random(0,255), random(0,255), random(0,255)));
    vector = sf::Vector2f(float(random(-LOWER_BOUND, LOWER_BOUND)), float(random(-LOWER_BOUND, LOWER_BOUND)));
}

void Circle::draw(sf::RenderWindow& window, sf::Time& elapsed) {
    sf::Vector2f pos = circle.getPosition();
    sf::Int64 deltaT = elapsed.asMicroseconds();
    sf::Vector2f delta(vector.x*deltaT/10000, vector.y*deltaT/10000);
    pos += delta;
    if (pos.x<=0||pos.x>=window.getView().getSize().x-circleSize*2) {
        vector.x = -vector.x;
    }
    if (pos.y<=0||pos.y>=window.getView().getSize().y-circleSize*2) {
        vector.y = -vector.y;            
    }

    if (pos.x>window.getView().getSize().x-circleSize*2) { // edge bug
        pos.x=window.getView().getSize().x-circleSize*2;
    } else if (pos.y>window.getView().getSize().y-circleSize*2) {
        pos.y=window.getView().getSize().y-circleSize*2;
    } else if (pos.x<0) {
        pos.x = 0;
    } else if (pos.y<0) {
        pos.y = 0;
    }

    circle.setPosition(pos);
    window.draw(circle);
}

#endif // CIRCLE_H