#include "TicTacToeTrainer.h"

TicTacToeTrainer::TicTacToeTrainer(Net _neuralNet) : neuralNet(topology)
{
	neuralNet = _neuralNet;
}

void TicTacToeTrainer::Train(int trainingCycles, int generationsPerCycle)
{
    int triainingPas = 0;
    std::vector<double> inputVals, targetVals, resultVals;

    for (int i = 0; i < trainingCycles; i++)
    {
        double xWin = 0, oWin = 0, draw = 0;
        std::cout << i + 1 << ". Cycle: " << std::endl;

        for (int j = 0; j < generationsPerCycle; j++, triainingPas++)
        {
            int gamePass = 0;
            int winner = 0;
            int bestMove = 0;
            bool xMove = false;
            std::vector<double> bestResultVals;
            GameLogic trainingGame;
            for (int k = 0; k < trainingGame.gridSize * trainingGame.gridSize; k++) bestResultVals.push_back(-1);


            while (!trainingGame.endGame)
            {
                gamePass++;

                neuralNet.feedForward(trainingGame.gameScore);
                neuralNet.getResults(resultVals);

                int AIChoice = helpers.largest_element_index(resultVals, trainingGame.gameScore);

                bestMove = ticTacToe3Algorithm.bestMove(trainingGame.gameScore);
                bestResultVals[bestMove] = 1;
                trainingGame.updateTableScore(AIChoice);
                neuralNet.backProp(bestResultVals);
                bestResultVals[bestMove] = 0;

                if (trainingGame.moveNumber > 4) winner = trainingGame.checkForWinner();
            }
            if (winner == 0) draw++;
            if (winner == 1) xWin++;
            if (winner == -1) oWin++;
        }
        std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;
        std::cout << "X: " << xWin / generationsPerCycle * 100 << "%\t";
        std::cout << "O: " << oWin / generationsPerCycle * 100 << "%\t";
        std::cout << "Draw: " << draw / generationsPerCycle * 100 << "%\t";
        std::cout << std::endl;
    }
}
