#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class SFWindow
{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    sf::Vector2i mousePosWindow;

    void initVeriables();
    void initWindow();
public:
    SFWindow();
    virtual ~SFWindow();

    void render();
    void update();
    void updateEvents();
};