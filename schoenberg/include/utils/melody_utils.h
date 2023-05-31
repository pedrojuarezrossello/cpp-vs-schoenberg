#ifndef MELODY_UTILS_H
#define MELODY_UTILS_H
#include <vector>

using std::vector;

vector<int> createRhythm(int numerator, int denominator);
vector<int> rhythmHelper(int beats, int count, double p);


#endif // MELODY_UTILS_H