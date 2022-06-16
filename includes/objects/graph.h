#ifndef GRAPH_H
#define GRAPH_H

#include <Vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../str_to_infix/str_to_infix.h"
#include "../constants/windowConstants.h"
#include "../plot/plot.h"
#include "../point/point.h"
#include "../random/random.h"
#include "../queue/MyQueue.h"

class Graph {

    public:
    Graph();

    void plot();
    void reset();
    void draw(sf::RenderWindow& window);
    void resize(sf::Vector2f size);
    void zoom(float factor, sf::Vector2i mousePos);
    void move(sf::Vector2f deltaPos);
    void addExpression(string str);

    sf::CircleShape origin;
    sf::View view;
    sf::RectangleShape background;
    vector<Queue <Token*>> expressions;
    vector<sf::CircleShape> dots;
    vector<sf::RectangleShape> lines;
    float scale = 1;

};

Graph::Graph() {
    view.reset(sf::FloatRect(0,0, SCREEN_WIDTH*GRAPH_WIDTH_RATIO, SCREEN_HEIGHT));
    view.setViewport(sf::FloatRect(0,0,GRAPH_WIDTH_RATIO,1));

    origin = sf::CircleShape(5);
    origin.setOrigin(origin.getRadius(), origin.getRadius());
    origin.setPosition(view.getSize()/2.f);

    background.setSize(view.getSize());
    background.setFillColor(graphColor);

    lines.emplace_back(sf::Vector2f(background.getSize().x*3, 1));
    lines.emplace_back(sf::Vector2f(1, background.getSize().y*3));
    for (int i=0; i<2; i++) {
        lines[i].setOrigin(lines[i].getSize()/2.f);
        lines[i].setPosition(origin.getPosition());
    }
}

void Graph::plot() {
    int lower_bound = (-origin.getPosition().x)/CONST_SCALE*scale, upper_bound = (view.getSize().x-origin.getPosition().x)/CONST_SCALE*scale;
    for (int i=0; i<expressions.size(); i++) {
        Queue<Point> points = PlotExpression(expressions[i], lower_bound, upper_bound, (upper_bound-lower_bound)/res);

        if(points.empty()) return;

        for (Queue<Point>::Iterator it = points.begin(); it!=points.end(); it++) {
            sf::CircleShape circle(2);
            circle.setPosition(sf::Vector2f(origin.getPosition().x+it->getVector().x*CONST_SCALE/scale, origin.getPosition().y-it->getVector().y*CONST_SCALE/scale));
            dots.push_back(circle);
        }
    }
}
    

void Graph::reset() {
    dots.clear();
}

void Graph::draw(sf::RenderWindow& window) {
    window.setView(view);
    window.draw(background);
    //window.draw(origin);
    for (int i=0; i<dots.size(); i++) {
        window.draw(dots[i]);
    }
    for (int i=0; i<lines.size(); i++) {
        window.draw(lines[i]);
    }

    window.setView(window.getDefaultView());
}

void Graph::resize(sf::Vector2f size) {
        view.reset(sf::FloatRect(0,0,size.x*GRAPH_WIDTH_RATIO, size.y));
        origin.setPosition(view.getSize()/2.f);
        for (int i=0; i<2; i++) {
            lines[i].setPosition(origin.getPosition());
        }
        background.setSize(view.getSize());
        reset();
        plot();
}

void Graph::zoom(float factor, sf::Vector2i mousePos) {
    if (background.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        if (factor<0) scale/= (-factor)/3;
        else scale *= (factor+1)/5;
    }
    if (scale<0.075) scale = 0.075;
    if (scale>1000) scale = 1000;
    std::cout << scale << std::endl;
    reset();
    plot();
}

void Graph::move(sf::Vector2f deltaPos) {
    origin.move(deltaPos);
    for (int i=0; i<dots.size(); i++) {
        dots[i].move(deltaPos);
    }
    for (int i=0; i<lines.size(); i++) {
        lines[i].move(deltaPos);
    }
    reset();
    plot();
}

void Graph::addExpression(string str) {
    Queue<Token*> infix = strToInfix(str);
    ShuntingYard sy(infix);
    expressions.push_back(sy.postfix());
    plot();
}


#endif // CIRCLE_H