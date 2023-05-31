#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <vector>
#include <mx/api/ScoreData.h>

using std::vector;
using std::string;
using std::default_random_engine;
using mx::api::ScoreData;

default_random_engine getRandomEngine();
int randomLength();
vector<vector<int>> calculatePartition(int num);
vector<int> randomPartition(int num);
void rescale(vector<int>& vec, int scalar);
inline int correctPitch(int pitch)
{
	//pitch mod 12 (0 ... 11)
	return (pitch % 12 >= 0) ? (pitch % 12) : ((pitch % 12) + 12);
}
void writeMusicXMLFile(const ScoreData& score, string&& file_path, bool write_to_console);
#endif //UTILS_H
