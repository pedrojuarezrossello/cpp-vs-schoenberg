#include "melody.h"
#include "utils.h"

Melody::Melody(const size_t number_of_notes) : row(TwelveToneRow()), melody_contour(std::vector<int>()), last_index(0) {}

std::vector<int> Melody::generate()
{
	return std::vector<int>();
}

std::vector<int> Melody::getMelody() const
{
	return melody_contour;
}

