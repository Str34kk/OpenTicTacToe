#pragma once
#include <iostream>
#include <vector>

class GameLogic
{
    private:
        void initVeriables();
    public:
        int gridSize = 3;
        int moveNumber;
        std::vector<double> gameScore;
        std::vector<int> tableScore;
        int player;
        bool endGame;

        GameLogic();
        virtual ~GameLogic();

        int checkForWinner();
        void updateTableScore(int index);
};

