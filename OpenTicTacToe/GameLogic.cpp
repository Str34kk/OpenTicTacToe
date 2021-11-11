#include "GameLogic.h"

void GameLogic::initVeriables()
{
    gridSize = 3;
    for (int i = 0; i < gridSize * gridSize; i++) gameScore.push_back(0);
    gameScore.push_back(1);
    tableScore = { 0, 0, 0, 0, 0, 0, 0, 0 };
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

int GameLogic::checkForWinner()
{
    for (int i = 0; i < gridSize * 2 + 2; i++)
    {
        if (tableScore[i] == gridSize)
        {
            endGame = true;
            return 1;
        }
        else if (tableScore[i] == -gridSize)
        {
            endGame = true;
            return -1;
        }
    }
    if (moveNumber == gridSize * gridSize)
    {
        endGame = true;
    }
    return 0;
}

void GameLogic::updateTableScore(int index)
{
    int col = index / 3;
    int row = index % 3;

    moveNumber += 1;
    gameScore[index] = gameScore.back();

    tableScore[col] += gameScore.back();
    tableScore[gridSize + row] += gameScore.back();
    if (row == col) tableScore[2 * gridSize] += gameScore.back();
    if (gridSize - 1 - col == row) tableScore[2 * gridSize + 1] += gameScore.back();
    gameScore.back() = -gameScore.back();
}
