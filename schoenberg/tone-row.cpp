#include "tone-row.h"
#include <chrono>
#include <random>

TwelveToneRow::TwelveToneRow() : row{ {0,1,2,3,4,5,6,7,8,9,10,11} }
{
	auto const seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(row.begin(), row.end(), std::default_random_engine(seed));
}

std::array<int,12> TwelveToneRow::getRow() const
{
	return row;
}

std::vector<int> TwelveToneRow::getRowSegment(size_t first, int length)
{
	int* rawRow = row.data();
	if (first + length < 12) {
		return std::vector<int>(rawRow + first, rawRow + first + length);
	} else {
		std::vector<int> output = std::vector<int>(rawRow + first, rawRow + 12);
		output.insert(output.end(), rawRow, rawRow+((first+length)%12));
		return output;
	}

}

void TwelveToneRow::_transposition(std::vector<int>& rowSegment, int degree)
{
	for (int& element : rowSegment)
	{
		element = (element + degree) % 12;
	}
}

void TwelveToneRow::_inversion(std::vector<int>& rowSegment)
{
	for (int& element : rowSegment)
	{
		element = ((2 * rowSegment[0] - element) % 12 >= 0) ? ((2 * rowSegment[0] - element) % 12) : (((2 * rowSegment[0] - element) % 12) + 12);
	}
}

void TwelveToneRow::_retrograde(std::vector<int>& rowSegment)
{
	std::reverse(rowSegment.begin(), rowSegment.end());
}

std::vector<int> TwelveToneRow::retrograde(size_t first, int length, int degree)
{
	auto rowSegment = getRowSegment(first, length);
	_retrograde(rowSegment);

	if (degree > 0) {
		_transposition(rowSegment, degree);
	}

	return rowSegment;
}

std::vector<int> TwelveToneRow::inversion(size_t first, int length, int degree)
{
	auto rowSegment = getRowSegment(first, length);
	_inversion(rowSegment);

	if (degree > 0) {
		_transposition(rowSegment, degree);
	}

	return rowSegment;
}

std::vector<int> TwelveToneRow::retrogradeInversion(size_t first, int length, int degree)
{
	auto rowSegment = getRowSegment(first, length);
	_inversion(rowSegment);
	_retrograde(rowSegment);

	if (degree > 0) {
		_transposition(rowSegment, degree);
	}

	return rowSegment;
}


