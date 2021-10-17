#pragma once
#include <vector>

class GameLogic
{
private:
    static constexpr int gridSize = 3;
    int gameScore[3][3] = { 0, 0, 0,
                            0, 0, 0,
                            0, 0, 0 };;
    int tableScore[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
    bool turnX;
    bool endGame;

    void initVeriables();
public:
    GameLogic();
    virtual ~GameLogic();
};

