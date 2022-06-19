#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

#include <cassert>
#include <sstream>
#include <Vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include "../objects/hoverableText.h"
#include "../constants/windowConstants.h"
#include "../point/point.h"
#include "../random/random.h"
#include "../queue/MyQueue.h"
#include "../objects/graph.h"

class SidePanel {


    public:
    SidePanel(sf::Font& newFont);

    void draw(sf::RenderWindow& window);
    void addExpression(Expression exp);
    void resize(sf::Vector2f size);

    sf::Font font;
    vector<hoverableText> expressionList;
    sf::View view;
    sf::RectangleShape background;

};

SidePanel::SidePanel(sf::Font& newFont) {
    font = newFont;

    view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH*(1-GRAPH_WIDTH_RATIO), SCREEN_HEIGHT));
    view.setViewport(sf::FloatRect(GRAPH_WIDTH_RATIO,0,1-GRAPH_WIDTH_RATIO,1));

    background.setSize(view.getSize());
    background.setFillColor(sidePanelColor);
}

void SidePanel::draw(sf::RenderWindow& window) {
    window.setView(view);
    window.draw(background);
    for (int i=0; i<expressionList.size(); i++) {
        expressionList[i].draw(window);
    }
}

void SidePanel::addExpression(Expression exp) {
    expressionList.emplace_back(font, "Y="+exp.getExpression(), exp.getColor(), sf::Vector2f(10, expressionList.size()*50+10));
}

void SidePanel::resize(sf::Vector2f size) {
    view.reset(sf::FloatRect(0,0,size.x*view.getViewport().width, size.y));
    background.setSize(view.getSize());
}


#endif //SIDE_PANEL_H