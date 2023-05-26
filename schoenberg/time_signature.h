#ifndef MEASURE_H
#define MEASURE_H
#include <stdexcept>

template<int Numerator, int Denominator,
	typename = typename std::enable_if<(Denominator == 4) || (Denominator == 8)>::type>
class TimeSignature
{
public:
	static int getNumerator() { return num; }
	static int getDenominator() { return den; }
private:
	static const int num = Numerator;
	static const int den = Denominator;
};

#endif // !MEASURE_H
