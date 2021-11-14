#include "Helpers.h"

void Helpers::showVectorVals(std::string label, std::vector<double>& v)
{
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }

    std::cout << std::endl;
}

int Helpers::largest_element_index(const std::vector<double>& resultVals, const std::vector<double>& gameScore)
{
    double largest_element = -1;

    for (int i = 0; i < resultVals.size(); i++)
    {
        if (resultVals[i] > resultVals[largest_element] && gameScore[i] == 0)
        {
            largest_element = i;
        }
    }

    return largest_element;
}
