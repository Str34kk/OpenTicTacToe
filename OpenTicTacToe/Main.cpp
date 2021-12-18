#include <SFML/Graphics.hpp>

#include "SFWindow.h"
#include "Net.h"
#include "TicTacToeTrainer.h"

int main()
{
    std::ofstream file;
    file.open("Data.txt");

    std::vector<unsigned> topology = { 10, 40, 40, 9 };
    Net neuralNet(topology);
    TicTacToeTrainer ticTacToeTrainer(neuralNet);
    neuralNet = ticTacToeTrainer.Train(1);

    std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;

    GameLogic gameLogic;
    SFWindow sFWindow(gameLogic, neuralNet);

    file << (char*)&neuralNet;
    file.close();

    while (sFWindow.getWindowIsOpen())
    {
        sFWindow.update();
        sFWindow.render();
    }
    return 0;
}