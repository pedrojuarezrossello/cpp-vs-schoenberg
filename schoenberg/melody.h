#ifndef MELODY_H
#define MELODY_H
#include "tone-row.h"
#include "time_signature.h"
#include <vector>

class Melody 
{
public:
	explicit Melody(const int number_of_bars, TimeSignature<int,int> measure);
	std::vector<std::pair<int, int>> generate();
	TimeSignature getMeasure() const;
private:
	TwelveToneRow row;
	TimeSignature measure;
	const int number_of_bars;
	std::vector<int> createRhythm(TimeSignature measure);
	std::vector<int> rhythmHelper(int beats, int count, double p);
};

#endif // !MELODY_H

