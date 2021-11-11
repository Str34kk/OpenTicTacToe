#pragma once
#include <vector>
#include "Neuron.h"

typedef std::vector<Neuron> Layer;

class Net
{
public:
	Net(const std::vector<unsigned>& topology);
	void feedForward(const std::vector<double>& inputVals);
	void backProp(const std::vector<double>& targetVals);
	void getResults(std::vector<double>& resultVals) const;
	double getRecentAverageError(void) const { return m_recentAverageError; }
private:
	std::vector<Layer> m_layers;
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};

