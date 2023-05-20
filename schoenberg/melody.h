#ifndef MELODY_H
#define MELODY_H
#include "tone-row.h"
#include <vector>

class Melody 
{
public:
	explicit Melody(const size_t number_of_notes);
	std::vector<int> generate();
	std::vector<int> getMelody() const;
private:
	const TwelveToneRow row;
	std::vector<int> melody_contour;
	
};




#endif // !MELODY_H

