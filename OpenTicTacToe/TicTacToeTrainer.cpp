#include "TicTacToeTrainer.h"

TicTacToeTrainer::TicTacToeTrainer(Net& _neuralNet) : neuralNet(_neuralNet)
{
    //m_trainingDataFile.open("ztest.txt");
    m_trainingDataFile.open("ttt3x3.txt");
}

Net TicTacToeTrainer::Train(int trainingCycles)
{
    int trainingPass = 0;
    std::vector<double> inputVals, targetVals, resultVals;

    for (int i = 0; i < trainingCycles; i++)
    {
        m_trainingDataFile.clear();
        m_trainingDataFile.seekg(0);
        while (!isEof())
        {
            trainingPass++;

            getNextInputs(inputVals, targetVals);

            neuralNet.feedForward(inputVals);

            neuralNet.backProp(targetVals);

            if (trainingPass % (10000 * trainingCycles) == 0)
            {
                std::cout << trainingPass << "th generation results" << std::endl;
                std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;
            }
            if (trainingPass % (1 * trainingCycles) == 0)
            {
                neuralNet.updateLearningRate();
            }
        }
    }
    std::cout << "final result" << std::endl;
    std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;
    return neuralNet;
}

unsigned TicTacToeTrainer::getNextInputs(std::vector<double>& inputVals, std::vector<double>& targetOutputVals)
{
    inputVals.clear();
    targetOutputVals.clear();
    int inputNeurons = 9;

    std::string line;
    std::getline(m_trainingDataFile, line);
    std::stringstream ss(line);

    double oneValue;
    int iteration = 0;
    while (ss >> oneValue) {
        if (iteration < inputNeurons) inputVals.push_back(oneValue);
        else targetOutputVals.push_back(oneValue);
        iteration++;
    }
    return 0;
}