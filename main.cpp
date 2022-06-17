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

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile(fontPath);   
    sf::Text fpsCounter("0", font);
    sf::Text dotCounter("0", font);
    sf::Text textBox("", font);
    dotCounter.move(sf::Vector2f(0,60));

    SidePanel sidePanel;
    Graph graph;

    // graph.addExpression("X");
    // graph.addExpression("sin(X)");
    // graph.addExpression("X^2");
    // graph.addExpression("X^3");
    // graph.addExpression("1");
    //graph.addExpression("X^(2/3)+(9/10)*(5-X^2)^(1/2)*sin(100*X)");       right 1/2 of heart

    sidePanel.updateList(graph);

    bool mouse1 = false;
    bool entering = false;

    string txt;

    sf::Vector2f LastPos, deltaPos(0,0);

    // run the program as long as the window is open
    // this is your main loop:
    while (window.isOpen()){
        window.setFramerateLimit(framerate);
        sf::Time elapsed = clock.restart();
        fpsCounter.setString(to_string(1000000/elapsed.asMicroseconds()));
        dotCounter.setString(to_string(graph.dots.size()));
        
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
                if (mouse1&&graph.background.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    deltaPos = sf::Vector2f(event.mouseMove.x-LastPos.x, event.mouseMove.y-LastPos.y);
                    graph.move(deltaPos);
                    LastPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                } else if (mouse1) {
                    mouse1 = false;
                    graph.plot();
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
                            sidePanel.updateList(graph);
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
                            graph.plot();
                            sidePanel.updateList(graph);
                    default:
                        break;
                }
                cout << "key " << event.key.code << " was pressed..."<<endl;
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    mouse1 = graph.background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                    LastPos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                }

                for (int i=0; i<sidePanel.expressionList.size(); i++) {
                    sf::FloatRect sidePanelBounds = sidePanel.expressionList[i].getGlobalBounds();
                    sidePanelBounds.left += graph.view.getSize().x;
                    if (sidePanelBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Color color(fastrand(255),fastrand(255),fastrand(255));
                            sidePanel.expressionList[i].setFillColor(color);
                            graph.expressions[i].setColor(color);
                        } else if (event.mouseButton.button == sf::Mouse::Right) {
                            graph.expressions.erase(graph.expressions.begin()+i);
                            sidePanel.updateList(graph);
                        }
                        graph.plot();
                    }
                }

                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mouse1) {
                        graph.plot();
                        mouse1 = false;
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

        sidePanel.draw(window);
        // window.draw(fpsCounter);
        // window.draw(dotCounter);
        window.display();

    }

    cout<<"------ NORMAL TERMINATION: WINDOW CLOSED!"<<endl;
    return 0;
}