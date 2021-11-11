#include <SFML/Graphics.hpp>

#include "SFWindow.h"
#include "Net.h"

int main()
{
    std::vector<unsigned> topology = { 9,36,36,9 };
    Net neuralNet(topology);
    GameLogic gameLogic;
    SFWindow sFWindow(gameLogic);

    std::vector<double> inputVals;
    neuralNet.feedForward(inputVals);
    std::vector<double> targetVals;
    neuralNet.feedForward(targetVals);
    std::vector<double> resultVals;
    neuralNet.feedForward(resultVals);

    while (sFWindow.getWindowIsOpen())
    {
        sFWindow.update();
        sFWindow.render();
    }
    return 0;
}