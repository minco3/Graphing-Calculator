#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

#include <sstream>
#include <Vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../constants/windowConstants.h"
#include "../point/point.h"
#include "../random/random.h"
#include "../queue/MyQueue.h"

class SidePanel {


    public:
    SidePanel();

    void draw(sf::RenderWindow& window);
    void updateList(Graph& graph);
    void resize(sf::Vector2f size);

    private:
    sf::Font font;
    vector<sf::Text> expressionList;
    sf::View view;
    sf::RectangleShape background;

};

SidePanel::SidePanel() {
    font.loadFromFile("../../CascadiaCode-Regular.ttf");

    view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH*(1-GRAPH_WIDTH_RATIO), SCREEN_HEIGHT));
    view.setViewport(sf::FloatRect(GRAPH_WIDTH_RATIO,0,1-GRAPH_WIDTH_RATIO,1));

    background.setSize(view.getSize());
    background.setFillColor(sidePanelColor);
}

void SidePanel::draw(sf::RenderWindow& window) {
    window.setView(view);
    window.draw(background);
    for (int i=0; i<expressionList.size(); i++) {
        window.draw(expressionList[i]);
    }
}

void SidePanel::updateList(Graph& graph) {
    for (int i=0; i<graph.expressions.size(); i++) {
        sf::Text txt("Y="+graph.expressions[i].getExpression(), font);
        txt.setFillColor(graph.expressions[i].getColor());
        txt.move(0, 150+i*50);
        expressionList.push_back(txt);
    }
}

void SidePanel::resize(sf::Vector2f size) {
    view.reset(sf::FloatRect(0,0,size.x*(1-GRAPH_WIDTH_RATIO), size.y));
    background.setSize(view.getSize());
}


#endif //SIDE_PANEL_H