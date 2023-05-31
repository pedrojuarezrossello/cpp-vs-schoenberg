#include "../include/utils/score_utils.h"
#include "../include/utils/tables.h"
#include "../include/utils/utils.h"
#include <unordered_map>
#include <unordered_set>

using std::vector;
using mx::api::NoteData;
using mx::api::MeasureData;
using mx::api::PartData;
using mx::api::ClefSymbol;
using  mx::api::Accidental;
using mx::api::Beam;


void createNote(NoteData& note, const int pitch, const int duration, int tick_count, const BeamPosition beam_position, bool no_altered)
{
	const auto noteInfo = chromaticScale.find(pitch)->second;

	note.pitchData.step = get<0>(noteInfo); //pitch
	note.pitchData.octave = get<1>(noteInfo); //octave
	note.pitchData.alter = get<2>(noteInfo); //accidental

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

	if (no_altered) //if it doesn't require alteration 
	{
		note.pitchData.accidental = Accidental::none;
	}

	const auto [durationName, durationDots] = rhythmLookUpTable.find(duration)->second; //obtain duration
	note.durationData.durationName = durationName;
	note.durationData.durationDots = durationDots;
	note.tickTimePosition = tick_count;

	switch (beam_position)

	{
	case BeamPosition::START:
		note.beams.push_back(Beam::begin);
		break;

	case BeamPosition::MIDDLE:
		note.beams.push_back(Beam::extend);
		break;

	case BeamPosition::END:
		note.beams.push_back(Beam::end);
		break;

	case BeamPosition::NO_BEAM:
		break;
	}

}

void addNoteToMeasure(MeasureData* measure, const int pitch, const int duration, int tick_count, const BeamPosition beam_position, bool no_altered)
{
	const auto staff = &measure->staves.front();
	staff->voices[0].notes.emplace_back(); //add new note
	auto& note = staff->voices[0].notes.back();
	createNote(note, pitch, duration, tick_count, beam_position, no_altered); //update the note (as of now empty)
}

MeasureData* addMeasure(PartData& part)
{
	part.measures.emplace_back();
	auto measure = &part.measures.back();

	measure->staves.emplace_back();
	return measure;
}

MeasureData* addFirstMeasure(PartData& part, int numerator, int denominator)
{
	part.measures.emplace_back(); //add a measure (first measure!) to the part

	auto measure = &part.measures.back();

	measure->timeSignature.beats = numerator; //measure info + clef etc
	measure->timeSignature.beatType = denominator;
	measure->timeSignature.isImplicit = false;

	measure->staves.emplace_back();
	const auto staff = &measure->staves.front();

	staff->clefs.emplace_back();
	const auto clef = &staff->clefs.back();

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
