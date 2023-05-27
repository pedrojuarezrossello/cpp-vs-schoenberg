#include "melody.h"
#include "include/melody_utils.h"
#include <chrono>
#include <random>

#include "utils.h"

using std::pair;
using std::make_pair;

template<int Numerator,int Denominator>
vector<pair<int,int>> Melody<Numerator,Denominator>::generate() 
{
	vector<int> rhythmicSchema;

	for (int i = 0; i<number_of_bars; i++) //creates a rhythm of number_of_bars bars
	{
		vector<int> barUnit = createRhythm(time_signature.getNumerator(),time_signature.getDenominator());
		rhythmicSchema.insert(rhythmicSchema.end(), barUnit.begin(), barUnit.end());
	}

	vector<pair<int, int>> melody_contour;

	const int number_of_notes = rhythmicSchema.size(); 
	int remaining{ number_of_notes };
	int last_row_index{ 0 };
	int last_rhythm_index{ 0 };

	while (remaining > 0)
	{
		int length = randomLength();

		if (remaining < length) //if we are the end and we get a length that's larger than the remaining notes
		{
			length = remaining;
		}

		vector<int> row_fragment = row.randomFragment(last_row_index,length); //get a random fragment from the row (from last processed index)
		for (int i = 0; i<row_fragment.size(); i++)
		{
			melody_contour.emplace_back(make_pair(row_fragment[i], rhythmicSchema[last_rhythm_index + i]));
		}
		//update values 
		last_row_index = (last_row_index + length) % 12; //go round the row
		last_rhythm_index += length;
		remaining -= length;
	}

	return melody_contour;
}

