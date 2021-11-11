#pragma once
#include <vector>

class TicTacToe3Algorithm
{
public:
	int bestMove(const std::vector<double> gameScore);

private:
	int evaluate(std::vector<double> gameScore);
	int minimax(std::vector<double> gameScore, int depth, bool isMax);
};

