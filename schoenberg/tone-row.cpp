#include "tone-row.h"
#include "include/tone_row_utils.h"
#include "include/utils.h"
#include <chrono>
#include <random>

using std::vector;
using std::array;

TwelveToneRow::TwelveToneRow() : row{ {-5,-4,-3,-2,-1,0,1,2,3,4,5,6} },
transformations{ {Transformation::INVERSION, Transformation::RETROGRADE, Transformation::RETROGRADE_INVERSION}}
{
	auto generator = getRandomEngine();

	//we initialise the tone row with a random permutation and position the transformation in a random order
	std::ranges::shuffle(row.begin(), row.end(), generator);
	std::ranges::shuffle(transformations.begin(), transformations.end(), generator);
}

array<int,12> TwelveToneRow::getRow() const
{
	return row;
}

vector<int> TwelveToneRow::getRowSegment(const size_t first, const int length) const 
{
	const auto it_to_row = row.cbegin();
	vector<int> rowSegment; //(N)RVO

	if (first + length < 12) { //if the row segment doesn't overflow on the right
		rowSegment.insert(rowSegment.end(), it_to_row + first, it_to_row + first + length);
		return rowSegment;
	}
	//if it does, insert the overflown elements from the beginning (in a circular fashion)
	rowSegment = std::vector<int>(it_to_row + first, it_to_row + 12);
	rowSegment.insert(rowSegment.end(), it_to_row, it_to_row+((first+length)%12));
	return rowSegment;
}

Transformation TwelveToneRow::updateTransformationQueue()
{
	auto generator = getRandomEngine();

	std::normal_distribution<double> normalDistribution(0.0, 1.0);
	const double normalSample = normalDistribution(generator); //will determine the transformation

	Transformation transformation;

	if (normalSample < 0)  //front of the queue - dequeue and enqueue first element
	{
		transformation = transformations.front();
		transformations.pop_front();
		transformations.push_back(transformation);
	}
	else if ((normalSample >= 0) || (normalSample < 1)) //middle of the queue (costly, but only with p=0.35)
	{
		const Transformation front_element = transformations.front();	//swap middle and last elements
		transformations.pop_front();
		transformation = transformations.front();
		transformations.pop_front();
		transformations.push_front(front_element);
		transformations.push_back(transformation);
	}
	else  //back of the queue - do nothing
	{
		transformation = transformations.back();
	}

	return transformation;
}

std::vector<int> TwelveToneRow::retrograde(size_t first, int length, int degree) const
{
	auto rowSegment = getRowSegment(first, length);
	retrogradeHelper(rowSegment);
	transpositionHelper(rowSegment, degree);

	return rowSegment;
}

std::vector<int> TwelveToneRow::inversion(size_t first, int length, int degree) const
{
	auto rowSegment = getRowSegment(first, length);
	inversionHelper(rowSegment);
	transpositionHelper(rowSegment, degree);

	return rowSegment;
}

std::vector<int> TwelveToneRow::retrogradeInversion(size_t first, int length, int degree) const
{
	auto rowSegment = getRowSegment(first, length);
	inversionHelper(rowSegment);
	retrogradeHelper(rowSegment);
	transpositionHelper(rowSegment, degree);

	return rowSegment;
}

std::vector<int> TwelveToneRow::randomFragment(size_t first, int length) 
{
	const Transformation transformation = updateTransformationQueue();

	auto generator = getRandomEngine();
	std::uniform_int_distribution<int> uniformDistribution(-6, 5);
	const int uniformSample = uniformDistribution(generator); //will determine degree of transposition

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


