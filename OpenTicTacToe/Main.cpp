#include <SFML/Graphics.hpp>

#include "SFWindow.h"
#include "Net.h"
#include "TicTacToeTrainer.h"
#include "TicTacToe3Algorithm.h"

int main()
{
    std::vector<unsigned> topology = { 10, 36, 36, 9 };
    Net neuralNet(topology);
    TicTacToeTrainer ticTacToeTrainer(neuralNet);
    GameLogic gameLogic;

    ticTacToeTrainer.Train(5, 100);

    SFWindow sFWindow(gameLogic, neuralNet);
    while (sFWindow.getWindowIsOpen())
    {
        sFWindow.update();
        sFWindow.render();
    }
    return 0;
}