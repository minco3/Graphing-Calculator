#ifndef HOVERABLE_TEXT_H
#define HOVERABLE_TEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../constants/windowConstants.h"

class hoverableText {

    public:

    hoverableText(sf::Font& newFont, sf::String str="", sf::Color color = sf::Color(255,255,255), sf::Vector2f pos = sf::Vector2f(0,0));
    hoverableText(const hoverableText& other);
    hoverableText& operator=(const hoverableText& RHS);

    void setText(sf::String str) {text.setString(str);}
    sf::String getText() {return text.getString();}
    void setColor(sf::Color color) {text.setFillColor(color);}
    sf::Color getColor() {return text.getFillColor();}

    sf::FloatRect getGlobalBounds() {return text.getGlobalBounds();}

    void draw(sf::RenderWindow& window);

    bool hovering;

    private:
    sf::Text text;
    sf::Font font;
    sf::RectangleShape highlight;


};

hoverableText::hoverableText(sf::Font& newFont, sf::String str, sf::Color color, sf::Vector2f pos) {
    font = newFont;
    text.setPosition(pos);
    text.setString(str);
    text.setFillColor(color);
    text.setFont(font);
    hovering=true;
    std::cout << static_cast<std::string>(text.getString()) << " " << text.getPosition().x << ", " << text.getPosition().y << std::endl;
}

void hoverableText::draw(sf::RenderWindow& window) {
    if (hovering) {
        highlight.setPosition(sf::Vector2f(text.getGlobalBounds().left-5, text.getGlobalBounds().top-5));
        highlight.setSize(sf::Vector2f(text.getGlobalBounds().width+15, text.getGlobalBounds().height+10));
        sf::Color highlightColor = sf::Color(50,50,50,highlight.getFillColor().a<100 ? highlight.getFillColor().a+3 : highlight.getFillColor().a);
        highlight.setFillColor(highlightColor);
        window.draw(highlight);
    } else {
        highlight.setFillColor(sf::Color(50,50,50,0));
    }
    window.draw(text);
}


hoverableText::hoverableText(const hoverableText& other) {
    font = other.font;
    text = other.text;
    highlight = other.highlight;
    hovering = other.hovering;
}

hoverableText& hoverableText::operator=(const hoverableText& RHS) {
    font = RHS.font;
    text = RHS.text;
    highlight = RHS.highlight;
    hovering = RHS.hovering;
    return *this;
}

#endif //HOVERABLE_TEXT_H