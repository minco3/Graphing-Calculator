#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <cstdlib>
#include <vector>

#include "includes/constants/windowConstants.h"
#include "includes/objects/graph.h"
#include "includes/objects/SidePanel.h"
#include "includes/random/random.h"

using namespace std;

int main()
{
    int framerate = 60;

    sf::FloatRect visibleArea;
    //----------S E T U P ------------------------------:

    //declare a window object:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "Graphing Calculator"
                            );

    window.setFramerateLimit(framerate);

    // call it once, after creating the window
    window.setVerticalSyncEnabled(true);
    //Application runs at the same freq as monitor

    sf::Cursor cursor;

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile(fontPath);   
    sf::Text fpsCounter("0", font);
    sf::Text dotCounter("0", font);
    sf::Text window_scale("0", font);
    sf::Text graph_scale("0", font);
    sf::Text textBox("", font);
    dotCounter.move(0,60);
    window_scale.move(0,120);
    graph_scale.move(0,180);

    sf::RectangleShape verticalBar(sf::Vector2f(VERTICAL_BAR_WIDTH ,SCREEN_HEIGHT));
    verticalBar.setFillColor(sf::Color(50,50,50));
    verticalBar.setPosition(SCREEN_WIDTH*GRAPH_WIDTH_RATIO-VERTICAL_BAR_WIDTH/2, 0);

    SidePanel sidePanel(font);
    Graph graph(font);
    graph.sidePanel = &sidePanel;

    // graph.addExpression("X");
    // graph.addExpression("sin(X)");
    // graph.addExpression("X^2");
    // graph.addExpression("X^3");
    // graph.addExpression("1");
    // graph.addExpression("X^(2/3)+(9/10)*(5-X^2)^(1/2)*sin(100*X)");       right 1/2 of heart

    bool movingGraph = false;
    bool changingRatio = false;
    bool entering = false;
    bool debug = false;
    
    float width_ratio = GRAPH_WIDTH_RATIO;

    string txt;

    sf::Vector2f LastPos, deltaPos(0,0);

    // run the program as long as the window is open
    // this is your main loop:
    while (window.isOpen()){
        window.setFramerateLimit(framerate);
        sf::Time elapsed = clock.restart();
        if (debug) {
            fpsCounter.setString(to_string(1000000/elapsed.asMicroseconds()));
            dotCounter.setString(to_string(graph.dots.size()));
            window_scale.setString(to_string(width_ratio));
            graph_scale.setString(to_string(graph.scale));
        }
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        

        //go through all the pending events: keyboard, mouse, close, resize, etc.
        //pollEvent and waitEvent are the only two functions that can fill event
        while (window.pollEvent(event))//or waitEvent: EVENT LOOP
        {
            // check the type of the event...
            switch (event.type)
            {
            // window closed
            // "close requested" event: we close the window
            case sf::Event::Closed:
                cout<<"close event was encountered!"<<endl;
                window.close();
                break;

            case sf::Event::MouseMoved:
                if (changingRatio||event.mouseMove.x>graph.background.getSize().x-4&&event.mouseMove.x<graph.background.getSize().x+4) {
                    if (cursor.loadFromSystem(sf::Cursor::SizeHorizontal))
                        window.setMouseCursor(cursor);
                } else if (!changingRatio) {
                    if (cursor.loadFromSystem(sf::Cursor::Arrow))
                        window.setMouseCursor(cursor);
                }
                    
                if (changingRatio) {
                    verticalBar.setPosition(sf::Vector2f(event.mouseMove.x, 0));
                }

                if (movingGraph&&graph.background.getGlobalBounds().contains(event.mouseMove.x-4, event.mouseMove.y)) {
                    deltaPos = sf::Vector2f(event.mouseMove.x-LastPos.x, event.mouseMove.y-LastPos.y);
                    graph.move(deltaPos);
                    LastPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                } else if (movingGraph) {
                    movingGraph = false;
                    graph.plot();
                }

                for (int i=0; i<sidePanel.expressionList.size(); i++) {
                    sf::FloatRect textBounds = sidePanel.expressionList[i].getGlobalBounds();
                    textBounds.left += graph.view.getSize().x;
                    if (textBounds.contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        sidePanel.expressionList[i].hovering = true;
                    }
                    else sidePanel.expressionList[i].hovering = false;
                }
                break;
                // key pressed
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case 26: //0
                        if (!entering&&event.key.control) graph.resetZoom();
                        break;
                    case 36: // ESC
                        if (entering) {
                            entering = false;
                            txt = "";
                            textBox.setString(txt);
                        }
                        break;
                    case 55: //+
                        if (!entering&&event.key.control) graph.zoom(1, static_cast<sf::Vector2i>(graph.background.getSize()/2.f));
                        break;
                    case 56: //-
                        if (!entering&&event.key.control) graph.zoom(-1, static_cast<sf::Vector2i>(graph.background.getSize()/2.f));
                        break;
                    case 58: // ENTER
                        if (entering) {
                            entering = false;
                            graph.addExpression(txt);
                            txt = "";
                            textBox.setString(txt);
                        } else {
                            entering = true;
                        }
                        break;
                    case 59: // BACKSPACE
                        if (entering&&txt.size()>0) {
                            txt = txt.substr(0, txt.size()-1);
                            textBox.setString(txt);
                        }
                        break;
                    case 66: //DEL
                        if (graph.expressions.size()>0)
                            graph.expressions.pop_back();
                            sidePanel.expressionList.pop_back();
                            graph.plot();
                            break;
                    case 87: //F3
                        debug = !debug;
                    default:
                        break;
                }
                cout << "key " << event.key.code << " was pressed..."<<endl;
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) { // MOUSE 1 PRESSED
                    //std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    sf::FloatRect verticalBarBounds = verticalBar.getGlobalBounds();
                    verticalBarBounds.left -=4;
                    verticalBarBounds.width +=6;
                    //std::cout << verticalBarBounds.left << ", " << verticalBarBounds.top << " in " <<  event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    changingRatio = verticalBarBounds.contains(event.mouseButton.x, event.mouseButton.y);
                    movingGraph = !changingRatio&&graph.background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                    if (movingGraph) LastPos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                }

                for (int i=0; i<sidePanel.expressionList.size(); i++) {
                    sf::FloatRect sidePanelBounds = sidePanel.expressionList[i].getGlobalBounds();
                    sidePanelBounds.left += graph.view.getSize().x;
                    if (sidePanelBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        if (event.mouseButton.button == sf::Mouse::Left) { // random color
                            sf::Color color(fastrand(255),fastrand(255),fastrand(255));
                            sidePanel.expressionList[i].setColor(color);
                            graph.expressions[i].setColor(color);
                        } else if (event.mouseButton.button == sf::Mouse::Right) { // remove expression
                            graph.expressions.erase(graph.expressions.begin()+i);
                            sidePanel.expressionList.erase(sidePanel.expressionList.begin()+i);
                            for (int j=i; j<sidePanel.expressionList.size(); j++) {
                                sidePanel.expressionList[j].move(0,-50);
                            }
                        }
                        graph.plot();
                    }
                }

                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) { // MOUSE 1 RELEASED
                    if (changingRatio) {
                        width_ratio /= graph.view.getSize().x/verticalBar.getPosition().x;
                        graph.view.setViewport(sf::FloatRect(0,0,width_ratio,1));
                        graph.resize(window.getDefaultView().getSize());
                        sidePanel.view.setViewport(sf::FloatRect(width_ratio,0,1-width_ratio,1));
                        sidePanel.resize(window.getDefaultView().getSize());
                        changingRatio = false;
                    }
                    if (movingGraph) {
                        graph.plot();
                        movingGraph = false;
                        deltaPos = sf::Vector2f(0,0);
                    }
                    //std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                }
                break;
            case sf::Event::MouseWheelScrolled:
                graph.zoom(event.mouseWheelScroll.delta, sf::Vector2i(event.mouseWheelScroll.x, event.mouseWheelScroll.y));
                break;
            case sf::Event::LostFocus:
                framerate/=2;
                break;
            case sf::Event::GainedFocus:
                framerate*=2;
                break;
            case sf::Event::Resized:
                graph.resize(sf::Vector2f(event.size.width, event.size.height));
                sidePanel.resize(sf::Vector2f(event.size.width, event.size.height));
                verticalBar.setSize(sf::Vector2f(VERTICAL_BAR_WIDTH, event.size.height));
                // verticalBar.setPosition(sf::Vector2f(event.size.width*width_ratio, 0));

                // update the view to the new size of the window
                visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            case sf::Event::TextEntered:
                if (event.text.unicode<128&&event.text.unicode!=8&&entering) {
                    textBox.setString(txt+=static_cast<char>(event.text.unicode));
                }
                break;
            default:
                break;
            }
        }

        // you HAVE TO clear your window on every iteration of this while.
        window.clear();
        graph.draw(window);
        if(entering) window.draw(textBox);
        if (debug) {
            window.draw(fpsCounter);
            window.draw(dotCounter);
            window.draw(window_scale);
            window.draw(graph_scale);
            window.draw(graph.origin);
        }
        sidePanel.draw(window);
        window.setView(window.getDefaultView());
        window.draw(verticalBar);
        window.display();

    }

    cout<<"------ NORMAL TERMINATION: WINDOW CLOSED!"<<endl;
    return 0;
}