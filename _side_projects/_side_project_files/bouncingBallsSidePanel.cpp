#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <cstdlib>
#include <vector>

#include "../../includes/objects/bouncingCircle.h"
#include "../../includes/random/random.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;
const int CELL_SIZE = 5;

const float GRAPH_WIDTH_RATIO = 0.6f;

using namespace std;

int main()
{
    int framerate = 60;
    float zoom;

    sf::FloatRect visibleArea;

    srand(time(NULL));
    //----------S E T U P ------------------------------:

    //declare a window object:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "JAVA IS FOR WUSSIES!"
                            );

    window.setFramerateLimit(framerate);
    
    sf::View graph(sf::FloatRect(0,0, SCREEN_WIDTH*GRAPH_WIDTH_RATIO, SCREEN_HEIGHT));
    graph.setViewport(sf::FloatRect(0,0,GRAPH_WIDTH_RATIO,1));


    sf::RectangleShape grayBG(graph.getSize());
    grayBG.setFillColor(sf::Color(70,70,70));

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
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    window.setView(graph);
                    if (event.mouseButton.x<window.getView().getSize().x&&event.mouseButton.y<window.getView().getSize().y)
                        circles.emplace_back(event.mouseMove.x, event.mouseMove.y);
                }
                break;
                // key pressed
            case sf::Event::KeyPressed:
                //cout << "key " << event.key.code << " was pressed..."<<endl;
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    window.setView(graph);
                    if (event.mouseButton.x<window.getView().getSize().x&&event.mouseButton.y<window.getView().getSize().y)
                        circles.emplace_back(event.mouseButton.x, event.mouseButton.y);
                }
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
                graph.reset(sf::FloatRect(0,0,event.size.width*GRAPH_WIDTH_RATIO, event.size.height));
                grayBG.setSize(graph.getSize());
                // update the view to the new size of the window
                visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            default:
                break;
            }
        }


        // you HAVE TO clear your window on every iteration of this while.
        window.clear();
        window.setView(graph);
        window.draw(grayBG);
        for (int i=0; i<circles.size(); i++) {
            circles[i].draw(window, elapsed);
        }
        window.draw(fpsCounter);
        window.display();

    }

    cout<<"------ NORMAL TERMINATION: WINDOW CLOSED!"<<endl;
    return 0;
}