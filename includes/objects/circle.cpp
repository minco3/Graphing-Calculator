#include "circle.h"

Circle::Circle() {
    circleSize = random(LOWER_BOUND, UPPER_BOUND);
    circle = sf::CircleShape(circleSize);
    circle.setFillColor(sf::Color(random(0,255), random(0,255), random(0,255)));
    vector = sf::Vector2f(float(random(-LOWER_BOUND, LOWER_BOUND))/10, float(random(-LOWER_BOUND, LOWER_BOUND))/10);
}

void Circle::draw(sf::RenderWindow& window) {
    sf::Vector2f pos = circle.getPosition();
    pos += vector;
    if (pos.x<=0+circleSize||pos.x>=window.getSize().x-circleSize) {
        vector.x = -vector.x;
    }
    if (pos.y<=0||pos.y>=window.getSize().y) {
        vector.y = -vector.y;            
    }
    circle.setPosition(pos);
    window.draw(circle);
}