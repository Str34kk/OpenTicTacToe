#include <SFML/Graphics.hpp>

#include "SFWindow.h"
#include "Net.h"
#include "TicTacToeTrainer.h"

int main()
{
    std::vector<unsigned> topology = { 10, 36, 36, 9 };
    Net neuralNet(topology);
    TicTacToeTrainer ticTacToeTrainer(neuralNet);
    neuralNet = ticTacToeTrainer.Train(10);

    std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;

    GameLogic gameLogic;
    SFWindow sFWindow(gameLogic, neuralNet);

    while (sFWindow.getWindowIsOpen())
    {
        sFWindow.update();
        sFWindow.render();
    }
    return 0;
}