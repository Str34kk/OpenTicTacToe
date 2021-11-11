#include <SFML/Graphics.hpp>

#include "SFWindow.h"
#include "Net.h"

void showVectorVals(std::string label, std::vector<double>& v)
{
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }

    std::cout << std::endl;
}

int largest_element_index(const std::vector<double>& resultVals, const std::vector<double>& gameScore)
{
    double largest_element = 0;

    for (int i = 0; i < resultVals.size(); i++)
    {
        if (resultVals[i] > resultVals[largest_element] && gameScore[i] == 0)
        {
            largest_element = i;
        }
    }

    return largest_element;
}

int main()
{
    std::vector<unsigned> topology = { 10, 36, 36, 9 };
    Net neuralNet(topology);
    GameLogic gameLogic;
    SFWindow sFWindow(gameLogic);

    //---------------------------------------
    
    int trainingCycles = 10;
    int triainingPas = 0;
    std::vector<double> inputVals, targetVals, resultVals;

    for (int i = 0; i < trainingCycles; i++)
    {
        double xWin = 0, oWin = 0, draw = 0;
        std::cout << i + 1 << ". Cycle: " << std::endl;

        for (int j = 0; j < 10000; j++, triainingPas++)
        {
            int gamePas = 0;
            int winner = 0;
            std::vector<std::vector<double>> gameStates;
            std::vector<int> AIChoiceStates;
            GameLogic trainingGame;

            while (!trainingGame.endGame)
            {
                gamePas++;
                gameStates.push_back(trainingGame.gameScore);

                neuralNet.feedForward(trainingGame.gameScore);
                neuralNet.getResults(resultVals);

                int AIChoice = largest_element_index(resultVals, trainingGame.gameScore);
                AIChoiceStates.push_back(AIChoice);

                trainingGame.updateTableScore(AIChoice);

                if (trainingGame.moveNumber > 4) winner = trainingGame.checkForWinner();
            }
            if (winner == 0) draw++;
            else
            {
                std::vector<double> smoothedResultVals;
                for (int k = 0; k < trainingGame.gridSize * trainingGame.gridSize; k++) smoothedResultVals.push_back(0);

                for (int k = gamePas - 1; k > 1; k -= 2)
                {
                    smoothedResultVals[AIChoiceStates[k]] = 1;
                    neuralNet.feedForward(gameStates[k]);
                    neuralNet.backProp(smoothedResultVals);
                    smoothedResultVals[AIChoiceStates[k]] = 0;
                }

                if (winner == 1)
                {
                    xWin++;
                }
                if (winner == -1)
                {
                    oWin++;
                }
            }
        }
        std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;
        std::cout << "X: " << xWin / 100 << "%\t";
        std::cout << "O: " << oWin / 100 << "%\t";
        std::cout << "Draw: " << draw / 100 << "%\t";
        std::cout << std::endl;
    }

    //---------------------------------------

    while (sFWindow.getWindowIsOpen())
    {
        sFWindow.update();
        sFWindow.render();
    }
    return 0;
}