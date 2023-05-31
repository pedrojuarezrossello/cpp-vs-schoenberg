#ifndef TONE_ROW_H
#define TONE_ROW_H

#include <array>
#include <deque>
#include <vector>

using std::array;
using std::vector;
using std::deque;

enum class Transformation
{
	INVERSION,
	RETROGRADE,
	RETROGRADE_INVERSION
};

class TwelveToneRow
{
	using melodyFragment = vector<int>;
	using Row = array<int, 12>;

public:
	TwelveToneRow();
	melodyFragment randomFragment(size_t first, int length);

private:
	Row row;
	deque<Transformation> transformations; //stores the transformations according to the order they've been used
	melodyFragment getRowSegment(size_t first, int length) const;
	Transformation updateTransformationQueue();
	melodyFragment inversion(size_t first, int length, int degree) const;
	melodyFragment retrograde(size_t first, int length, int degree) const;
	melodyFragment retrogradeInversion(size_t first, int length, int degree) const;

};

#endif //TONE_ROW_H 