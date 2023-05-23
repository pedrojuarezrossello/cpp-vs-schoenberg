#include <iostream>
#include "chromatic-scale.h"
#include "melody.h"
#include "tone-row.h"
#include "utils.h"

int main() {

	Measure measure(2, 4);
	Melody melody(4, measure);

	auto melody_four_bars = melody.generate();

	for (auto a : melody_four_bars)
	{
		std::cout << '(' << a.first << "," << a.second << ')' << " ";
	}

	return 0;
}