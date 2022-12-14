#ifndef GRAPH_H
#define GRAPH_H

#include <Vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../expression/expression.h"
#include "../str_to_infix/str_to_infix.h"
#include "../constants/windowConstants.h"
#include "../plot/plot.h"
#include "../point/point.h"
#include "../random/random.h"
#include "../queue/MyQueue.h"
#include "../objects/SidePanel.h"

class Graph {

    public:
    Graph(sf::Font& newFont);

    void plot();
    void reset();
    void draw(sf::RenderWindow& window);
    void resize(sf::Vector2f size);
    void zoom(float factor, sf::Vector2i mousePos);
    void resetZoom();
    void move(sf::Vector2f deltaPos);
    void addExpression(std::string str);
    void updateBounds();
    void updateGraphLines();

    SidePanel* sidePanel;

    sf::View view;
    sf::CircleShape origin;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text lowerBound;
    sf::Text upperBound;
    vector<Expression> expressions;
    vector<sf::CircleShape> dots;
    vector<sf::RectangleShape> lines;
    vector<sf::RectangleShape> axis;
    vector<sf::RectangleShape> graphLinesX;
    vector<sf::RectangleShape> graphLinesY;

    int rangeX;
    int rangeY;
     
    float scale = 1;

};

Graph::Graph(sf::Font& newFont) {

    font = newFont;

    lowerBound.setFont(font);
    lowerBound.setCharacterSize(15);
    upperBound.setFont(font);
    upperBound.setCharacterSize(15);


    view.reset(sf::FloatRect(0,0, SCREEN_WIDTH*GRAPH_WIDTH_RATIO, SCREEN_HEIGHT));
    view.setViewport(sf::FloatRect(0,0,GRAPH_WIDTH_RATIO,1));

    origin = sf::CircleShape(5);
    origin.setOrigin(origin.getRadius(), origin.getRadius());
    origin.setPosition(view.getSize()/2.f);

    background.setSize(view.getSize());
    background.setFillColor(graphColor);

    axis.emplace_back(sf::Vector2f(background.getSize().x*3, 1));
    axis.emplace_back(sf::Vector2f(1, background.getSize().y*3));
    for (int i=0; i<axis.size(); i++) {
        axis[i].setOrigin(axis[i].getSize()/2.f);
        axis[i].setPosition(origin.getPosition());
        axis[i].setFillColor(sf::Color::Black);
    }

    sf::RectangleShape lineX(sf::Vector2f(1, SCREEN_HEIGHT*3));
    lineX.setOrigin(lineX.getSize().x/2, lineX.getSize().y*0.3f);
    lineX.setFillColor(graphLineColor);
    graphLinesX.push_back(lineX);

    sf::RectangleShape lineY(sf::Vector2f(SCREEN_WIDTH*3, 1));
    lineY.setOrigin(lineY.getSize().x*0.3f, lineY.getSize().y/2);
    lineY.setFillColor(graphLineColor);
    graphLinesY.push_back(lineY);

    for (int i=0; i<GRAPH_LINE_COUNT; i++) { // X AXIS
        graphLinesX.emplace_back(graphLinesX[0]);
    }

    for (int i=0; i<GRAPH_LINE_COUNT; i++) { // Y AXIS
        graphLinesY.emplace_back(graphLinesY[0]);
    }

    updateBounds();
    updateGraphLines();
}

void Graph::plot() {
    reset();
    float lower_bound = (-origin.getPosition().x)/CONST_SCALE*scale, upper_bound = (view.getSize().x-origin.getPosition().x)/CONST_SCALE*scale;
    for (int i=0; i<expressions.size(); i++) {
        if (expressions[i].isLinear()) {
            
            float length = PlotLine(expressions[i].postfix, lower_bound, upper_bound);
            sf::RectangleShape line(sf::Vector2f(length*CONST_SCALE/scale*10,4));
            line.setOrigin(line.getSize()/2.f);
            line.setPosition(origin.getPosition().x, origin.getPosition().y-(expressions[i].getIntercept()*CONST_SCALE/scale));
            line.setRotation(-atan(expressions[i].getSlope())*180.f/M_PI);
            line.setFillColor(expressions[i].color);
            lines.push_back(line);
            //std::cout << "length : " << length << "slope: " << expressions[i].getSlope() << "rotation :" << atan(expressions[i].getSlope())*180.f/M_PI << "intercept :" << expressions[i].getIntercept() << std::endl; 
        } else {
            Queue<Point> points = PlotExpression(expressions[i].postfix, lower_bound, upper_bound, (upper_bound-lower_bound)/res);

            if(points.empty()) return;

            for (Queue<Point>::Iterator it = points.begin(); it!=points.end(); it++) {
                sf::CircleShape circle(2);
                circle.setPosition(sf::Vector2f(origin.getPosition().x+it->getVector().x*CONST_SCALE/scale, origin.getPosition().y-it->getVector().y*CONST_SCALE/scale));
                circle.setFillColor(expressions[i].color);
                dots.push_back(circle);
            }
        }
    }
}
    

void Graph::reset() {
    lines.clear();
    dots.clear();
}

void Graph::draw(sf::RenderWindow& window) {
    window.setView(view);
    window.draw(background);

    for (int i=0; i<min(rangeX,(int)graphLinesX.size()); i++) {
        window.draw(graphLinesX[i]);
    }
    for (int i=0; i<min(rangeY,(int)graphLinesY.size()); i++) {
        window.draw(graphLinesY[i]);
    }
    for (int i=0; i<axis.size(); i++) {
        window.draw(axis[i]);
    }
    for (int i=0; i<dots.size(); i++) {
        if (background.getGlobalBounds().contains(dots[i].getPosition()));
            window.draw(dots[i]);
    }
    for (int i=0; i<lines.size(); i++) {
        window.draw(lines[i]);
    }

    window.draw(lowerBound);
    window.draw(upperBound);
}

void Graph::resize(sf::Vector2f size) {
    view.reset(sf::FloatRect(0,0,size.x*view.getViewport().width, size.y));
    origin.setPosition(view.getSize()/2.f);
    for (int i=0; i<2; i++) {
        axis[i].setPosition(origin.getPosition());
    }
    background.setSize(view.getSize());
    reset();
    plot();
    updateBounds();
    updateGraphLines();
}

void Graph::zoom(float factor, sf::Vector2i mousePos) {
    if (background.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        //sf::Vector2f distanceFromOrigin((origin.getPosition().x-(background.getSize().x/2)), origin.getPosition().y-(background.getSize().y/2));
        sf::Vector2f distanceFromOrigin(origin.getPosition().x-mousePos.x, origin.getPosition().y-mousePos.y);
    
        if (factor<0) {
            scale*= 1.1f;
            move(distanceFromOrigin*-0.1f);
        } 
        else{
            scale *= 0.9f;
            move(distanceFromOrigin*0.1f);
        } 
    }
    if (scale<0.075) scale = 0.075;
    if (scale>10) scale = 10;
    // std::cout << scale << std::endl;
    reset();
    plot();
    updateBounds();
}

void Graph::move(sf::Vector2f deltaPos) {
    origin.move(deltaPos);
    for (int i=0; i<axis.size(); i++) {
        axis[i].move(deltaPos);
    }
    for (int i=0; i<graphLinesX.size(); i++) {
        graphLinesX[i].move(deltaPos);
    }
    for (int i=0; i<graphLinesY.size(); i++) {
        graphLinesY[i].move(deltaPos);
    }
    for (int i=0; i<dots.size(); i++) {
        dots[i].move(deltaPos);
    }
    for (int i=0; i<lines.size(); i++) {
        lines[i].move(deltaPos);
    }
    updateBounds();
    updateGraphLines();
}

void Graph::resetZoom() {
    origin.setPosition(view.getSize()/2.f);
    for (int i=0; i<axis.size(); i++)
        axis[i].setPosition(origin.getPosition());
    scale=1;
    reset();
    plot();
    updateBounds();
    updateGraphLines();
}

void Graph::addExpression(std::string str) {
    Queue<Token*> q = strToInfix(str);
    if (!q.empty()) {
        expressions.emplace_back(str);
        sidePanel->addExpression(expressions.back());
        reset();
        plot();
    }
}

void Graph::updateBounds() {
    float lower = (-origin.getPosition().x)/CONST_SCALE*scale, upper = (view.getSize().x-origin.getPosition().x)/CONST_SCALE*scale;

    lowerBound.setString(to_string(lower));
    upperBound.setString(to_string(upper));

    lowerBound.setOrigin(0, lowerBound.getGlobalBounds().height);
    upperBound.setOrigin(lowerBound.getGlobalBounds().width, lowerBound.getGlobalBounds().height);

    lowerBound.setPosition(0,view.getSize().y-50);
    upperBound.setPosition(view.getSize().x, view.getSize().y-50);
}

void Graph::updateGraphLines() {
    float lower = (0-origin.getPosition().x)/CONST_SCALE*scale, upper = (view.getSize().x-origin.getPosition().x)/CONST_SCALE*scale;
    float lowerY = (0-origin.getPosition().y)/CONST_SCALE*scale, upperY = (view.getSize().y-origin.getPosition().y)/CONST_SCALE*scale;
    
    int graphLineScale = scale>=1 ? (int)scale : 1;

    rangeX = (upper-lower)/graphLineScale+2;
    rangeY = (upperY-lowerY)/graphLineScale+2;

    //std::cout<< int(lower) << ", " << int(upper) << "\n" << int(lowerY) << ", " << int(upperY) << "scale" << graphLineScale << std::endl;


    for (int i=0; i<rangeX; i++) { //X AXIS
        if (i>graphLinesX.size())
            graphLinesX.emplace_back(graphLinesX[0]);
        graphLinesX[i].setPosition(((int(lower)-int(lower)%graphLineScale)+i*graphLineScale)*CONST_SCALE/scale+origin.getPosition().x, 0);
    }


    for (int i=0; i<rangeY; i++) { // Y AXIS
        if (i>graphLinesY.size())
            graphLinesY.emplace_back(graphLinesY[0]);
        // std::cout << int(lowerY)+i*graphLineGapY << std::endl;
        graphLinesY[i].setPosition(0, ((int(lowerY)-int(lowerY)%graphLineScale)+i*graphLineScale)*CONST_SCALE/scale+origin.getPosition().y);
    }

}


#endif // CIRCLE_H