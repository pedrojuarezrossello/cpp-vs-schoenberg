#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <vector>

using std::vector;
using std::default_random_engine;

default_random_engine getRandomEngine();
int randomLength();
vector<vector<int>> calculatePartition(int num);
vector<int> randomPartition(int num);
void rescale(vector<int>& vec, int scalar);
int correctPitch(int pitch);

#endif //UTILS_H
