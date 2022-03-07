#include <SFML/Graphics.hpp>

#include "SFWindow.h"
#include "Net.h"
#include "TicTacToeTrainer.h"

int main()
{
    int trainCycles;
    std::cout << "Enter the number of training cycles: ";
    std::cin >> trainCycles;


    std::vector<unsigned> topology = { 10, 120, 120, 9 };
    Net neuralNet(topology);
    TicTacToeTrainer ticTacToeTrainer(neuralNet);
    neuralNet = ticTacToeTrainer.Train(trainCycles);

    std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;

    SFWindow sFWindow(neuralNet);

    while (sFWindow.getWindowIsOpen())
    {
        sFWindow.update();
        sFWindow.render();
    }
    return 0;
}