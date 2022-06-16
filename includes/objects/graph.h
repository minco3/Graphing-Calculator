#ifndef GRAPH_H
#define GRAPH_H

const float GRAPH_WIDTH_RATIO = 0.6f;
const int LOWER_BOUND = 10, UPPER_BOUND = 20;
const sf::Color bgColor(70,70,70);

#include <Vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../constants/windowConstants.h"
#include "../point/point.h"
#include "../random/random.h"
#include "../queue/MyQueue.h"

class Graph {

    public:
    Graph();

    void plot(Queue<Point> &points);
    void reset();
    void draw(sf::RenderWindow& window);
    void resize(sf::Vector2f size);
    void zoom(float factor, sf::Vector2i mousePos);

    private:
    sf::View view;
    sf::RectangleShape background;
    sf::RectangleShape shape;
    vector<sf::CircleShape> dots;

};

Graph::Graph() {
    view.reset(sf::FloatRect(0,0, SCREEN_WIDTH*GRAPH_WIDTH_RATIO, SCREEN_HEIGHT));
    view.setViewport(sf::FloatRect(0,0,GRAPH_WIDTH_RATIO,1));

    background.setSize(view.getSize());
    background.setFillColor(bgColor);
    std::cout << background.getGlobalBounds().width;
}

void Graph::plot(Queue<Point> &points) {
    if(points.empty()) return;
    for (Queue<Point>::Iterator it = points.begin(); it!=points.end(); it++) {
        std::cout << it->getVector().y << std::endl; 
        sf::CircleShape circle(3);
        circle.setPosition(it->getVector());
        dots.push_back(circle);
    }
}

void Graph::reset() {
    dots.empty();
}

void Graph::draw(sf::RenderWindow& window) {
    window.setView(view);
    window.draw(background);
    if (!dots.empty()) {
        for (int i=0; i<dots.size(); i++) {
            window.draw(dots[i]);
        }
    }
    window.draw(shape);

}

void Graph::resize(sf::Vector2f size) {
        view.reset(sf::FloatRect(0,0,size.x*GRAPH_WIDTH_RATIO, size.y));
        background.setSize(view.getSize());
}

void Graph::zoom(float factor, sf::Vector2i mousePos) {
    if (background.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        std::cout << factor << std::endl;
    }
}


#endif // CIRCLE_H