#include <SFML/Graphics.hpp>

#include "SFWindow.h"
#include "Net.h"
#include "TicTacToeTrainer.h"

int main()
{
    srand(1);
    int trainCycles;
    std::cout << "Enter the number of training cycles: ";
    std::cin >> trainCycles;


    /*std::vector<unsigned> topology = { 9, 300, 93, 29, 9 };*/
    /*std::vector<unsigned> topology = { 9, 300, 51, 9 };*/
    std::vector<unsigned> topology = { 9, 126, 33, 9 };
    /*std::vector<unsigned> topology = { 9, 36, 36, 9 };*/
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