#include <SFML/Graphics.hpp>

#include "SFWindow.h"
#include "Net.h"
#include "TicTacToeTrainer.h"

int main()
{

    std::vector<unsigned> topology = { 10, 40, 40, 9 };
    Net neuralNet(topology);
    TicTacToeTrainer ticTacToeTrainer(neuralNet);
    neuralNet = ticTacToeTrainer.Train(50);

    std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;

    SFWindow sFWindow(neuralNet);

    while (sFWindow.getWindowIsOpen())
    {
        sFWindow.update();
        sFWindow.render();
    }
    return 0;
}