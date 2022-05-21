#include "Neuron.h"

double Neuron::eta = 0.012;
double Neuron::alpha = 0.005;

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for (unsigned c = 0; c < numOutputs; c++) {
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight()/10;
	}

	m_myIndex = myIndex;
}

void Neuron::feedForward(Layer& prevLayer)
{
	double sum = 0.0;

	// Sum the previous layer's outputs (which are our inputs)
	// Include the bias node from the previous layer.

	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		sum += prevLayer[n].getOutputVal() *
			prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = Neuron::transferFunction(sum);
}


void Neuron::calcOutputGradients(double targetVal)
{
	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcHiddenGradients(const Layer& nextLayer)
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::updateInputWeights(Layer& prevLayer)
{
	// The weights to be updated are in the Connection container
	// in the neurons in the preceding layer

	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		Neuron& neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight =
			// Individual input, magnified by the gradient and train rate:
			eta
			* neuron.getOutputVal()
			* m_gradient
			// Also add momentum = a fraction of the previous delta weight;
			+ alpha
			* oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}

double Neuron::transferFunction(double x)
{
	// tanh - output range [-1.0..1.0]
	// return tanh(x);

	// relu - output range [0.0..x]
	if (x > 0.0) return x;
	//return 0.0;
	// leaky relu - output range [0.0..x]
	return 0.0001 * x;
}

double Neuron::transferFunctionDerivative(double x)
{
	// tanh derivative
	// return 1.0 - tanh(x) * tanh(x);

	// relu derivative
	if (x > 0.0) return 1.0;
	return 0.0001;
}

double Neuron::sumDOW(const Layer& nextLayer) const
{
	double sum = 0.0;

	// Sum our contributions of the errors at the nodes we feed.

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}
