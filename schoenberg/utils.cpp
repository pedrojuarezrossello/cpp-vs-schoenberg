#include "utils.h"

#include <chrono>
#include <random>
#include <unordered_map>

int randomLength()
{
	const long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::bernoulli_distribution distribution(0.65);
	
	if (distribution(generator)) [[likely]] {
		std::uniform_int_distribution<int> middleDistribution(4, 8);
		return middleDistribution(generator);
	} else
	{
		const std::vector<int> extremes{2, 3, 9, 10, 11, 12};
		std::uniform_int_distribution<int> extremeDistribution(0, 4);
		return extremes[extremeDistribution(generator)];
	}
}

std::vector<std::vector<int>> _partition(int num) {
	std::unordered_map<int, std::vector<std::vector<int>>> partitionMemoisation({ { 1,{{1}} } });
	std::vector<std::vector<int>> output{{{num}} };

	if (partitionMemoisation.contains(num)) 
	{
		return partitionMemoisation[num];
	}
	for (int i=1; i<num; i++)
	{
		int first = num - i;
		std::vector<std::vector<int>> prev = _partition(i);
		for (std::vector<int> part : prev)
		{
			part.push_back(first);
			output.push_back(part);
		}
	}

	partitionMemoisation[num] = output;
	return output;
}

std::vector<int> beatPartition(int num)
{
	const long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::vector<std::vector<int>> partitions = _partition(num);
	std::uniform_int_distribution<int> randomPartitionDistribution(0, partitions.size());
	return partitions[randomPartitionDistribution(generator)];
}

