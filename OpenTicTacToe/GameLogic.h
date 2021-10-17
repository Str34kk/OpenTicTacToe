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
        std::vector<std::vector<int>> gameScore;
        std::vector<int> tableScore;
        bool turnX;
        bool endGame;

        GameLogic();
        virtual ~GameLogic();

        void checkForWinner();
        void updateTableScore(int col, int row, int score);
};

