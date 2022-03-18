#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "GameLogic.h"
#include "Net.h"
#include "Helpers.h"

class SFWindow
{
    private:
        Helpers helpers;
        GameLogic gameLogic;
        Net neuralNet;

        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;
        sf::Vector2i mousePosition;
        sf::Texture tablet;
        sf::Texture sprite;
        sf::Sprite table;
        sf::Sprite x1, x2, x3, o1, o2, o3;
        std::vector<sf::Sprite> o;
        std::vector<sf::Sprite> x;

        int aiMove;

        void initVeriables();
        void initWindow();
        void AIMove();
        void Test(int testCycles);
    public:
        SFWindow(Net& _neuralNet);
        virtual ~SFWindow();

        const bool getWindowIsOpen() const;
        void render();
        void update();
        void updateEvents();
};