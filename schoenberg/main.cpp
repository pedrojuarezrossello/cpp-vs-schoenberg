#include <iostream>
#include "chromatic-scale.h"
#include "tone-row.h"
#include "utils.h"

int main() {

	/*TwelveToneRow testRow;
	const auto row = testRow.getRow();

	for (const int i : row)
	{
		std::cout << i << " ";
	}

	std::cout << '\n';

	const auto rowSeg = testRow.randomFragment(4,10);
	for (const int i : rowSeg)
	{
		std::cout << i << " ";
	}

	std::cout << '\n';

	const auto rowInverted = testRow.inversion(4, 10,2);
	for (int i : rowInverted)
	{
		std::cout << i << " ";
	}

	std::cout << '\n';*/
	auto part = beatPartition(8);
	for (auto a : part)
	{
		
			std::cout << a << " ";
		
		std::cout << '\n';
	}

	return 0;
}