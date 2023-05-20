#include <iostream>
#include "chromatic-scale.h"
#include "tone-row.h"

int main() {

	TwelveToneRow testRow;
	const auto row = testRow.getRow();

	for (const int i : row)
	{
		std::cout << i << " ";
	}

	std::cout << '\n';

	const auto rowSeg = testRow.getRowSegment(4,10);
	for (const int i : rowSeg)
	{
		std::cout << i << " ";
	}

	std::cout << '\n';

	auto rowInverted = testRow.inversion(4, 10,0);
	for (int i : rowInverted)
	{
		std::cout << i << " ";
	}

	return 0;
}