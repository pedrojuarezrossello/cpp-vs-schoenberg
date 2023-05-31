#include "../include/utils/melody_utils.h"
#include "../include/utils/utils.h"

using std::bernoulli_distribution;
using std::make_move_iterator;

vector<int> rhythmHelper(const int beats, const int count, const double p)
{
	auto generator = getRandomEngine();

	bernoulli_distribution do_we_stop_decomposing(p); //determines if we go down another level of recursion

	vector<int> beat_decomposition = randomPartition(beats); //obtain random partition 
	vector<int> output; //(n)rvo

	if (count == 0 || do_we_stop_decomposing(generator)) //if we've reached the semiquaver level or we've randomly decided to stop decomposing
	{
		output.assign(make_move_iterator(beat_decomposition.begin()), make_move_iterator(beat_decomposition.end())); //move vectors
		beat_decomposition.erase(beat_decomposition.begin(), beat_decomposition.end()); //clean up 
		rescale(output, static_cast<int>(pow(2.0, static_cast<double>(count)))); //rescale the beat decomposition so it's expressed in semiquavers
		return output;
	}

	for (const int duration : beat_decomposition) //else we decompose further going down the tree DFS
	{
		vector<int> beat_sub_decomposition = rhythmHelper(2 * duration, count - 1, p + 0.1); //times two since we express the duration value in half-as-long values
		output.insert(output.end(), beat_sub_decomposition.begin(), beat_sub_decomposition.end());
	}

	return output;
}

vector<int> createRhythm(const int numerator, const int denominator)
{
	//if denominator is 8, then the beat unit is a quaver so we recurse one fewer time
	return (denominator == 8) ? rhythmHelper(numerator, 1, 0.21) : rhythmHelper(numerator, 2, 0.25);
}