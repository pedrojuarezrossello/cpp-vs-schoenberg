#ifndef TONE_ROW_H
#define TONE_ROW_H
#include <array>
#include <vector>

class TwelveToneRow
{
	using melodyFragment = std::vector<int>;
	using Row = std::array<int, 12>;

public:
	TwelveToneRow();
	Row getRow() const;
	melodyFragment inversion(size_t first, int length, int degree);
	melodyFragment retrograde(size_t first, int length, int degree);
	melodyFragment retrogradeInversion(size_t first, int length, int degree);
	melodyFragment getRowSegment(size_t first, int length);
	melodyFragment randomFragment(size_t first, int length);

private:
	Row row;
	static void _transposition(melodyFragment& rowSegment, int degree);
	static void _inversion(melodyFragment& rowSegment); 
	static void _retrograde(melodyFragment& rowSegment);
};

#endif //TONE_ROW_H 