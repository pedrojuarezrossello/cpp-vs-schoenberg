#include "tone-row.h"
#include <chrono>
#include <random>

TwelveToneRow::TwelveToneRow() : row{ {-5,-4,-3,-2,-1,0,1,2,3,4,5,6} },
transformations{ {Transformation::INVERSION, Transformation::RETROGRADE, Transformation::RETROGRADE_INVERSION}}
{
	auto const seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::ranges::shuffle(row.begin(), row.end(), std::default_random_engine(seed));
	std::ranges::shuffle(transformations.begin(), transformations.end(), std::default_random_engine(seed));
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
	if (degree > 5 || degree < -6) [[unlikely]]
	{
		throw std::invalid_argument("Degree must be between -6 and 5!");
	}
	for (int& element : rowSegment)
		{
			element = (element + degree) % 12;
		}
}

void TwelveToneRow::_inversion(std::vector<int>& rowSegment)
{
	for (int& element : rowSegment)
	{
		element = ((2 * rowSegment[0] - element) % 12);
	}
}

void TwelveToneRow::_retrograde(std::vector<int>& rowSegment)
{
	std::ranges::reverse(rowSegment.begin(), rowSegment.end());
}

std::vector<int> TwelveToneRow::retrograde(size_t first, int length, int degree)
{
	auto rowSegment = getRowSegment(first, length);
	_retrograde(rowSegment);
	_transposition(rowSegment, degree);

	return rowSegment;
}

std::vector<int> TwelveToneRow::inversion(size_t first, int length, int degree)
{
	auto rowSegment = getRowSegment(first, length);
	_inversion(rowSegment);
	_transposition(rowSegment, degree);

	return rowSegment;
}

std::vector<int> TwelveToneRow::retrogradeInversion(size_t first, int length, int degree)
{
	auto rowSegment = getRowSegment(first, length);
	_inversion(rowSegment);
	_retrograde(rowSegment);
	_transposition(rowSegment, degree);

	return rowSegment;
}

std::vector<int> TwelveToneRow::randomFragment(size_t first, int length) 
{
	const long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::normal_distribution<double> normalDistribution(0.0, 1.0);
	std::uniform_int_distribution<int> uniformDistribution(-6, 5);

	const double normalSample = normalDistribution(generator);
	const int uniformSample = uniformDistribution(generator);

	Transformation transformation;

	if (normalSample<0) {
		transformation = transformations.front();
		transformations.pop_front();
		transformations.push_back(transformation);
	} else if ((normalSample>=0) || (normalSample<1)) {
		const Transformation temp = transformations.front();
		transformations.pop_front();
		transformation = transformations.front();
		transformations.pop_front();
		transformations.push_front(temp);
		transformations.push_back(transformation);
	} else {
		transformation = transformations.back();
	}

	switch (transformation)
	{
	case Transformation::INVERSION:
		return inversion(first, length, uniformSample);
	case Transformation::RETROGRADE:
		return retrograde(first, length, uniformSample);
	case Transformation::RETROGRADE_INVERSION:
		return retrogradeInversion(first, length, uniformSample);
	}

	return std::vector<int>(length, 0);
}


