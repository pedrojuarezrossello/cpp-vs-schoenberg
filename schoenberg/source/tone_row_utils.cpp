#include "../include/utils/tone_row_utils.h"

#include <algorithm>
#include <stdexcept>

using std::vector;

void transpositionHelper(vector<int>& rowSegment, int degree)
{
	if (degree > 5 || degree < -6) [[unlikely]]
	{
		throw std::invalid_argument("Degree must be between -6 and 5!");
	}
		for (int& element : rowSegment)
		{
			element = (element + degree) % 12;
		}
}

void inversionHelper(vector<int>& rowSegment)
{
	for (int& element : rowSegment)
	{
		element = ((2 * rowSegment[0] - element) % 12);
	}
}

void retrogradeHelper(std::vector<int>& rowSegment)
{
	std::ranges::reverse(rowSegment.begin(), rowSegment.end());
}
