#include "../include/utils/utils.h"

#include <chrono>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <mx/api/DocumentManager.h>

using std::default_random_engine;
using std::chrono::system_clock;
using std::bernoulli_distribution;
using std::uniform_int_distribution;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using mx::api::DocumentManager;

default_random_engine getRandomEngine()
{
	const long long seed = system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	return generator;
}

int randomLength()
{
	auto generator = getRandomEngine();
	bernoulli_distribution distribution(0.65);

	//prioritise mid lengths of row segments
	if (distribution(generator)) [[likely]] {
		uniform_int_distribution<int> middleDistribution(4, 8);
		return middleDistribution(generator);
	}
	else
	{
		const vector<int> extremes{ 2, 3, 9, 10, 11, 12 };
		uniform_int_distribution<int> extremeDistribution(0, 4);
		return extremes[extremeDistribution(generator)];
	}
}

vector<vector<int>> calculatePartition(int num) {
	//calculate partitions of a number (4 = 1 + 1 + 2 and so on) excluding "unmusical" partitions

	unordered_map<int, vector<vector<int>>> partitionMemoisation({ { 1,{{1}} } });

	const unordered_set<int> prohibited_partitions = { 5,9,10,11,13,15 };
	vector<vector<int>> output;
	if (!prohibited_partitions.contains(num))
	{
		output = { {num} };
	}

	if (partitionMemoisation.contains(num))
	{
		return partitionMemoisation[num];
	}

	for (int i = 1; i < num; i++)
	{
		int first = num - i;
		if (!prohibited_partitions.contains(first) && !prohibited_partitions.contains(i)) {
			vector<vector<int>> prev = calculatePartition(i);
			for (vector<int> part : prev)
			{
				part.push_back(first);
				output.push_back(part);
			}
		}
	}

	partitionMemoisation[num] = output;
	return output;
}

vector<int> randomPartition(int num)
{
	//select a random partition of a number
	auto generator = getRandomEngine();
	vector<vector<int>> partitions = calculatePartition(num);
	uniform_int_distribution<int> randomPartitionDistribution(0, partitions.size() - 1);
	vector<int> partition = partitions[randomPartitionDistribution(generator)];
	return partition; //(n)rvo
}

void rescale(vector<int>& vec, int scalar)
{
	for (int& element : vec)
	{
		element *= scalar;
	}
}


