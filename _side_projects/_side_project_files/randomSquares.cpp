#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <cstdlib>
#include <vector>

#include "../../includes/random/random.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;
const int CELL_SIZE = 5;

using namespace std;

int main()
{
    sf::FloatRect visibleArea;
    
    int framerate = 8;

    srand(time(NULL));
    //----------S E T U P ------------------------------:

    //declare a window object:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "JAVA IS FOR WUSSIES!"
                            );
    //
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third arguments to set style
    //of the window: resize, fullscreen etc.
    //
    //or...
    // you could do this:
    //sf::RenderWindow window;
    //window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
    //                                                  "SFML window!");
    //

    window.setFramerateLimit(framerate);

    //this is where we keep all the shapes.
    //sf::RectangleShape shapeArray[GRID_HEIGHT][GRID_WIDTH];


    // call it once, after creating the window
    window.setVerticalSyncEnabled(true);
    //Application runs at the same freq as monitor

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("../../CascadiaCode-Regular.ttf");


    // define a 120x50 rectangle
    vector<vector<sf::RectangleShape>> rectangles(GRID_WIDTH);
    for (int x=0; x<GRID_WIDTH; x++) {
        for (int y=0; y<GRID_HEIGHT; y++) {
            rectangles[x].push_back(sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH/GRID_WIDTH, SCREEN_HEIGHT/GRID_HEIGHT)));
            rectangles[x][y].move(sf::Vector2f(SCREEN_WIDTH/GRID_WIDTH*x, SCREEN_HEIGHT/GRID_HEIGHT*y));
        }
    }
    sf::Text fpsCounter("0", font);

    // change the size to 100x100
    //rectangle.setSize(sf::Vector2f(10, 10));
    //. . . . . . . . . . . . . . . . . . . . . . . . . . .



    // run the program as long as the window is open
    // this is your main loop:
    while (window.isOpen()){
        window.setFramerateLimit(framerate);
        fpsCounter.setString(to_string(1000/clock.getElapsedTime().asMilliseconds()));
        clock.restart();
        
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

                // key pressed
            case sf::Event::Resized:
                // update the view to the new size of the window
                visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            case sf::Event::KeyPressed:
                cout << "key " << event.key.code << " was pressed..."<<endl;
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                else
                    std::cout<<"left button?"<<std::endl;
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
            default:
                break;
            }
        }

        // you HAVE TO clear your window on every iteration of this while.
        window.clear();
        for (int x=0; x<GRID_WIDTH; x++) {
            for (int y=0; y<GRID_HEIGHT; y++) {
                rectangles[x][y].setFillColor(sf::Color(fastrand(255), fastrand(255), fastrand(255)));
                window.draw(rectangles[x][y]);
            }
        }
        window.draw(fpsCounter);
        window.display();

    }

    cout<<"------ NORMAL TERMINATION: WINDOW CLOSED!"<<endl;
    return 0;
}