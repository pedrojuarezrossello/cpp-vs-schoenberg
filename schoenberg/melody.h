#ifndef MELODY_H
#define MELODY_H
#include "tone-row.h"
#include "time_signature.h"
#include <vector>

template<int Numerator, int Denominator>
class Melody 
{
public:
	explicit Melody(const int number_of_bars, TimeSignature<Numerator,Denominator> time_signature) :
								row(TwelveToneRow()),time_signature(time_signature), number_of_bars(number_of_bars) {}

	std::vector<std::pair<int, int>> generate();
	TimeSignature<Numerator, Denominator> getMeasure() const { return time_signature;};
private:
	TwelveToneRow row;
	TimeSignature<Numerator, Denominator> time_signature;
	const int number_of_bars;

};

#include "melody.cpp"
#endif // !MELODY_H

