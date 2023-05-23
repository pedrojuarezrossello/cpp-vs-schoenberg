#ifndef MEASURE_H
#define MEASURE_H
#include <stdexcept>

class Measure
{
public:
	Measure(const int num, const int den) : numerator(num), denominator(den) {} //throw read up on it!!!!
	[[nodiscard]] int getNumerator() const { return numerator; }
	[[nodiscard]] int getDenominator() const { return denominator; }
private:
	int numerator;
	int denominator;
};

#endif // !MEASURE_H
