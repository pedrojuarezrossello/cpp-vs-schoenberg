#include "include/score_utils.h"
#include "include/tables.h"
#include "utils.h"
#include <unordered_map>
#include <unordered_set>

using std::vector;
using std::unique_ptr;
using mx::api::NoteData;
using mx::api::MeasureData;
using mx::api::PartData;
using mx::api::StaffData;
using mx::api::ClefData;
using mx::api::ClefSymbol;
using  mx::api::Accidental;
using mx::api::Beam;

NoteData createNote(int pitch, int duration, int tickCount, bool start, bool middle, bool end, bool no_altered)
{
	auto note = NoteData{}; //check if we can remake this with void
	const auto noteInfo = chromaticScale.find(pitch)->second;

	note.pitchData.step = get<0>(noteInfo);
	note.pitchData.octave = get<1>(noteInfo);
	note.pitchData.alter = get<2>(noteInfo);

	if (get<2>(noteInfo) == -1)
	{
		note.pitchData.accidental = Accidental::flat;

	}
	else if (get<2>(noteInfo))
	{
		note.pitchData.accidental = Accidental::sharp;
	}
	else
	{
		note.pitchData.accidental = Accidental::natural; 
	}

	if (no_altered)
	{
		note.pitchData.accidental = Accidental::none;
	}

	const auto durationInfo = rhythmLookUpTable.find(duration)->second; //structed binding
	note.durationData.durationName = durationInfo.first;
	note.durationData.durationDots = durationInfo.second;
	note.tickTimePosition = tickCount;

	if (start)
	{
		note.beams.push_back(Beam::begin);
	}
	if (middle)
	{
		note.beams.push_back(Beam::extend);
	}
	if (end)
	{
		note.beams.push_back(Beam::end);
	}

	return note;
}

void addNoteToMeasure(MeasureData* measure, int pitch, int duration, int tickCount, bool start, bool middle, bool end, bool no_altered)
{
	auto staff = &measure->staves.front(); //careful!!
	staff->voices[0].notes.emplace_back(createNote(pitch, duration, tickCount, start, middle, end, no_altered)); //check this later
}

MeasureData* addMeasure(PartData& part)
{
	using namespace mx::api;
	part.measures.emplace_back(MeasureData{});
	auto measure = &part.measures.back();
	measure->staves.emplace_back(StaffData{});
	return measure;
}
MeasureData* addFirstMeasure(PartData& part, int numerator, int denominator)
{
	part.measures.emplace_back(); //add a measure (first measure!) to the part

	auto measure = &part.measures.back();

	measure->timeSignature.beats = numerator;
	measure->timeSignature.beatType = denominator;
	measure->timeSignature.isImplicit = false;

	measure->staves.emplace_back();
	auto staff = &measure->staves.front();

	staff->clefs.emplace_back();
	auto clef = &staff->clefs.back();

	clef->symbol = ClefSymbol::g;
	clef->line = 2;

	return measure;
}

void adjustAlterationTable(std::vector<bool>& alt, int pitch)
{
	//updates the alteration table (whether a note has been altered in the measure)

	const int pitch_corrected = correctPitch(pitch);

	if (naturals.contains(pitch_corrected)) //either first encounter OR a natural accidental => not altered anymore
	{
		switch (pitch_corrected)
		{
		case 1: //G
			alt[4] = false;
			break;
		case 3: //A
			alt[5] = false;
			break;
		case 5: //B
			alt[6] = false;
			break;
		case 6: //c
			alt[0] = false;
			break;
		case 8: //D
			alt[1] = false;
			break;
		case 10: //E
			alt[2] = false;
			break;
		case 11: //F
			alt[3] = false;
			break;
		}
	}
	else
	{
		switch (pitch_corrected) //sharp or flat, so now it is altered
		{
		case 0: //F sharp
			alt[3] = true;
			break;
		case 2: //G sharp
			alt[4] = true;
			break;
		case 4: //B flat
			alt[6] = true;
			break;
		case 7: //C sharp
			alt[0] = true;
			break;
		case 9: //E flat
			alt[2] = true;
			break;
		}
	}
}

bool alterationValueFromPitch(vector<bool>& alt, int pitch)
{
	//returns the alteration status (i.e if it has been altered previously in the bar) from the pitch data

	const int pitch_corrected = correctPitch(pitch);

	if (naturals.contains(pitch_corrected)) 
	{
		switch (pitch_corrected)
		{
		case 1: //G
			return alt[4];

		case 3: //A
			return alt[5];

		case 5: //B
			return alt[6];

		case 6: //c
			return alt[0];

		case 8: //D
			return alt[1];

		case 10: //E
			return alt[2];

		case 11: //F
			return alt[3];

		}
	}
	else
	{
		switch (pitch_corrected)
		{
		case 0: //F sharp
			return alt[3];

		case 2: //G sharp
			return alt[4];

		case 4: //B flat
			return alt[6];

		case 7: //C sharp
			return alt[0];

		case 9: //E flat
			return alt[2];

		}
	}
	return false;
}

bool isAltered(const int pitch)
{
	const int pitch_corrected = correctPitch(pitch);

	return  (naturals.contains(pitch_corrected)) ? false : true;

}
