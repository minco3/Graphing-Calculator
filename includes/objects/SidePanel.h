#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

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
    void resize(sf::Vector2f size);

    private:

    sf::View view;
    sf::RectangleShape background;

};

SidePanel::SidePanel() {
    view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH*(1-GRAPH_WIDTH_RATIO), SCREEN_HEIGHT));
    view.setViewport(sf::FloatRect(GRAPH_WIDTH_RATIO,0,1-GRAPH_WIDTH_RATIO,1));

    background.setSize(view.getSize());
    background.setFillColor(sidePanelColor);
    
    std::cout << background.getGlobalBounds().width;
}

void SidePanel::draw(sf::RenderWindow& window) {
    window.setView(view);
    window.draw(background);
}
void SidePanel::resize(sf::Vector2f size) {
    view.reset(sf::FloatRect(0,0,size.x*(1-GRAPH_WIDTH_RATIO), size.y));
    background.setSize(view.getSize());
}


#endif //SIDE_PANEL_H