#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <cstdlib>
#include <vector>

#include "includes/objects/circle.h"
#include "includes/random/random.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;
const int CELL_SIZE = 5;

using namespace std;

int main()
{

    sf::View graph(sf::FloatRect(0, 0, SCREEN_WIDTH*0.7f, SCREEN_HEIGHT));
    sf::View sidePanel(sf::FloatRect(SCREEN_WIDTH*0.7f, 0, SCREEN_WIDTH*0.3f, SCREEN_HEIGHT));
    
    graph.setViewport(sf::FloatRect(0, 0, 0.7f, 1));
    sidePanel.setViewport(sf::FloatRect(0.7f, 0, 0.3f, 1));

    int framerate = 60;

    sf::FloatRect visibleArea;

    sf::RectangleShape grayRect(sidePanel.getSize());
    grayRect.setFillColor(sf::Color(100, 100, 100));
    sf::RectangleShape darkerGrayRect(graph.getSize());
    darkerGrayRect.setFillColor(sf::Color(70, 70, 70));

    srand(time(NULL));
    //----------S E T U P ------------------------------:

    //declare a window object:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "Graphing Calculator"
                            );

    window.setFramerateLimit(framerate);

    //this is where we keep all the shapes.
    //sf::RectangleShape shapeArray[GRID_HEIGHT][GRID_WIDTH];


    // call it once, after creating the window
    window.setVerticalSyncEnabled(true);
    //Application runs at the same freq as monitor

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("../../CascadiaCode-Regular.ttf");   
    sf::Text fpsCounter("0", font);

    vector<Circle> circles;
    circles.emplace_back();


    // run the program as long as the window is open
    // this is your main loop:
    while (window.isOpen()){

        window.setFramerateLimit(framerate);
        sf::Time elapsed = clock.restart();
        fpsCounter.setString(to_string(1000000/elapsed.asMicroseconds()));
        
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
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    circles.emplace_back(event.mouseMove.x, event.mouseMove.y);
                break;
                // key pressed
            case sf::Event::KeyPressed:
                cout << "key " << event.key.code << " was pressed..."<<endl;
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    std::cout << "sidepanel size " << sidePanel.getSize().x << ", " << sidePanel.getSize().y << std::endl;
                }
                else if (event.mouseButton.x<window.getSize().x&&event.mouseButton.y<window.getSize().y)
                    //circles.emplace_back(event.mouseButton.x, event.mouseButton.y);
                break;
            case sf::Event::MouseWheelScrolled:
                framerate+=event.mouseWheelScroll.delta;
                break;
            case sf::Event::LostFocus:
                framerate/=2;
                break;
            case sf::Event::GainedFocus:
                framerate*=2;
                break;
            case sf::Event::Resized:
                // update the view to the new size of the window
                visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                graph.setViewport(sf::FloatRect(0, 0, 0.7f, 1));
                sidePanel.setViewport(sf::FloatRect(0.7f, 0, 0.3f, 1));
            default:
                break;
            }
        }


        // you HAVE TO clear your window on every iteration of this while.
        window.clear();
        window.setView(graph);
        window.draw(darkerGrayRect);
        for (int i=0; i<circles.size(); i++) {
            circles[i].draw(window, elapsed);
        }
        window.setView(sidePanel);
        window.draw(grayRect);
        window.draw(fpsCounter);
        window.display();

    }

    cout<<"------ NORMAL TERMINATION: WINDOW CLOSED!"<<endl;
    return 0;
}