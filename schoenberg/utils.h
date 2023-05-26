#ifndef UTILS_H
#define UTILS_H
#include <random>
#include <vector>
#include "TimeSignature.h"
#include <mx/api/MeasureData.h>
#include <mx/api/PartData.h>

using std::vector;

std::default_random_engine getRandomEngine();








int randomLength();
std::vector<std::vector<int>> calculatePartition(int num);
std::vector<int> randomPartition(int num);
void rescale(std::vector<int>& vec, int scalar);
mx::api::NoteData createNote(int pitch, int duration, int tickCount, bool start, bool middle, bool end, bool no_altered);
void addNoteToMeasure(mx::api::MeasureData* measureP, int pitch, int duration, int tickCount, bool start, bool middle, bool end, bool no_altered);
mx::api::MeasureData* addMeasure(mx::api::PartData& outPartData);
mx::api::MeasureData* addFirstMeasure(mx::api::PartData& outPartData, TimeSignature timeSignature);
void adjustAlterationTable(std::vector<bool>& alt, int pitch);
bool alterationValueFromPitch(const std::vector<bool>& alt, int pitch);
bool isAltered(int pitch);

#endif // !UTILS_H

