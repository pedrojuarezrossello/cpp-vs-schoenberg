#ifndef MELODY_H
#define MELODY_H
#include "tone-row.h"
#include "measure.h"
#include <vector>

class Melody 
{
public:
	explicit Melody(const int number_of_bars, Measure measure);
	std::vector<std::pair<int, int>> generate();

private:
	TwelveToneRow row;
	Measure measure;
	const int number_of_bars;
	std::vector<int> createRhythm(Measure measure);
	std::vector<int> rhythmHelper(int beats, int count, double p);
};

#endif // !MELODY_H

