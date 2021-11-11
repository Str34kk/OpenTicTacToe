#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Net.h"
#include "GameLogic.h"
#include "Helpers.h"
#include "TicTacToe3Algorithm.h"

class TicTacToeTrainer
{
public:
	TicTacToeTrainer(Net _neuralNet);
	void Train(int trainingCycles, int generationsPerCycle);

private:
	std::vector<unsigned> topology = { 1, 1, 1 };
	Net neuralNet;
	Helpers helpers;
	TicTacToe3Algorithm ticTacToe3Algorithm;
};

