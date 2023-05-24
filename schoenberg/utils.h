#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include "measure.h"
#include <mx/api/MeasureData.h>
#include <mx/api/PartData.h>

int randomLength();
std::vector<std::vector<int>> calculatePartition(int num);
std::vector<int> randomPartition(int num);
void rescale(std::vector<int>& vec, int scalar);

mx::api::NoteData createNote(int pitch, int duration, int tickCount);

void addNoteToMeasure(mx::api::MeasureData* measureP, int pitch, int duration, int tickCount);
mx::api::MeasureData* addMeasure(mx::api::PartData& outPartData);
mx::api::MeasureData* addFirstMeasure(mx::api::PartData& outPartData, Measure timeSignature);
#endif // !UTILS_H

