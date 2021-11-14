#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Net.h"
#include "GameLogic.h"
#include "Helpers.h"
#include <fstream>
#include <sstream>

class TicTacToeTrainer
{
public:
	TicTacToeTrainer(Net _neuralNet);
	void Train(int trainingCycles);
	bool isEof(void) { return m_trainingDataFile.eof(); }

	unsigned getNextInputs(std::vector<double>& inputVals, std::vector<double>& targetOutputVals);

private:
	Net neuralNet;
	Helpers helpers;
	std::ifstream m_trainingDataFile;
};

