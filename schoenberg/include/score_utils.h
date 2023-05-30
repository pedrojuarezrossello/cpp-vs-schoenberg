#ifndef SCORE_UTILS_H
#define SCORE_UTILS_H

#include <mx/api/MeasureData.h>
#include <mx/api/NoteData.h>
#include <mx/api/PartData.h>

using std::vector;
using std::unique_ptr;
using mx::api::NoteData;
using mx::api::MeasureData;
using mx::api::PartData;

enum class BeamPosition {
	START,
	MIDDLE,
	END,
	NO_BEAM
};

NoteData createNote(int pitch, int duration, int tick_count, BeamPosition beam_position, bool no_altered);
NoteData createNotesWithTie(int pitch, int first_beat, int duration, int tick_count, int semiquaversPerBeat, bool no_altered);
void addNoteToMeasure(MeasureData* measure, int pitch, int duration, int tick_count, BeamPosition beam_position, bool no_altered);
void addNoteWithTie(MeasureData* measure, int pitch, int first_beat, int duration, int tick_count, int semiquaversPerBeat, bool no_altered);
MeasureData* addMeasure(PartData& part);
MeasureData* addFirstMeasure(PartData& part, int numerator, int denominator);
void adjustAlterationTable(vector<bool>& alt, int pitch);
bool alterationValueFromPitch(vector<bool>& alt, int pitch);
bool isAltered(int pitch);


#endif // SCORE_UTILS_H