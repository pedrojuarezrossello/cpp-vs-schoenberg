#include "melody.h"

#include <chrono>
#include <random>

#include "utils.h"

Melody::Melody(const int number, Measure measure) : row(TwelveToneRow()), measure(measure), number_of_bars(number) {}

std::vector<std::pair<int,int>> Melody::generate()
{
	std::vector<int> rhythmicSchema({});
	for (int i = 0; i<number_of_bars; i++)
	{
		std::vector<int> barUnit = createRhythm(measure);
		rhythmicSchema.insert(rhythmicSchema.end(), barUnit.begin(), barUnit.end());
	}

	std::vector<std::pair<int, int>> melody_contour({});
	int number_of_notes = rhythmicSchema.size();
	int remaining{ number_of_notes };
	int last_index_pitch{ 0 };
	int last_index_rhythm{ 0 };

	while (remaining > 0)
	{
		int length = randomLength();
		if (remaining < length)
		{
			length = remaining;
		}

		std::vector<int> row_fragment = row.randomFragment(last_index_pitch,length);
		for (int i = 0; i<row_fragment.size(); i++)
		{
			melody_contour.emplace_back(std::make_pair(row_fragment[i], rhythmicSchema[last_index_rhythm + i]));
		}
		last_index_pitch = (last_index_pitch + length) % 12;
		last_index_rhythm += length;
		remaining -= length;
	}

	return melody_contour;
}

std::vector<int> Melody::rhythmHelper(int beats, int count, double p)
{
	const long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::bernoulli_distribution distribution(p);
	

	std::vector<int> temp = randomPartition(beats);
	std::vector<int> output;
	if (count == 0 || distribution(generator))
	{
		rescale(temp, static_cast<int>(pow(2.0,static_cast<double>(count))));
		return temp;
	}

	for (int element : temp)
	{
		std::vector<int> temp2 = rhythmHelper(2*element, count - 1, p + 0.1);
		output.insert(output.end(), temp2.begin(), temp2.end());
	}
	return output;
}

std::vector<int> Melody::createRhythm(Measure measure)
{
	const int numerator = measure.getNumerator();
	const int denominator = measure.getDenominator();
	if (denominator == 4)
	{
		return rhythmHelper(numerator, 1, 0.25);
	}
	return rhythmHelper(numerator, 2, 0.3);
}

