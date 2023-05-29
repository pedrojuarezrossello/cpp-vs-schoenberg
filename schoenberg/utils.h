#ifndef UTILS_H
#define UTILS_H
#include <random>
#include <vector>


using std::vector;

std::default_random_engine getRandomEngine();
int randomLength();
std::vector<std::vector<int>> calculatePartition(int num);
std::vector<int> randomPartition(int num);
void rescale(std::vector<int>& vec, int scalar);
int correctPitch(int pitch);

#endif // !UTILS_H

