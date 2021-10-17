#include "GameLogic.h"

void GameLogic::initVeriables()
{
    gridSize = 3;
    gameScore = { {0, 0, 0 },
                        {0, 0, 0 },
                        {0, 0, 0 }};
    tableScore = { 0, 0, 0, 0, 0, 0, 0, 0 };
	turnX = true;
	endGame = false;
    moveNumber = 0;
}

GameLogic::GameLogic()
{
	initVeriables();
}

GameLogic::~GameLogic()
{
}

void GameLogic::checkForWinner()
{
    for (int i = 0; i < gridSize * 2 + 2; i++)
    {
        if (tableScore[i] == gridSize)
        {
            std::cout << "X win";
            endGame = true;
            break;
        }
        else if (tableScore[i] == -gridSize)
        {
            std::cout << "O win";
            endGame = true;
            break;
        }
    }
}

void GameLogic::updateTableScore(int col, int row, int score)
{
    tableScore[col] += score;
    tableScore[gridSize + row] += score;
    if (row == col) tableScore[2 * gridSize] += score;
    if (gridSize - 1 - col == row) tableScore[2 * gridSize + 1] += score;
}
