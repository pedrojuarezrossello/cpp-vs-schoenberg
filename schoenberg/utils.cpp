#include "utils.h"

#include <chrono>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <mx/api/MeasureData.h>
#include <mx/api/PartData.h>

std::default_random_engine getRandomEngine()
{
	const long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	return generator;
}

std::unordered_map<int, std::tuple<mx::api::Step, int, int>> chromaticScale {
	{-11, std::make_tuple<>(mx::api::Step::g,4,0)},
	{-10, std::make_tuple<>(mx::api::Step::g,4,1)},
	{-9, std::make_tuple<>(mx::api::Step::a,4,0)},
	{-8, std::make_tuple<>(mx::api::Step::b,4,-1)},
	{-7, std::make_tuple<>(mx::api::Step::b,4,0)},
	{-6, std::make_tuple<>(mx::api::Step::c,5,0)},
	{-5, std::make_tuple<>(mx::api::Step::c,5,1)},
	{-4, std::make_tuple<>(mx::api::Step::d,5,0)},
	{-3, std::make_tuple<>(mx::api::Step::e,5,-1)},
	{-2, std::make_tuple<>(mx::api::Step::e,5,0)},
	{-1, std::make_tuple<>(mx::api::Step::f,5,0)},
	{0, std::make_tuple<>(mx::api::Step::f,5,1)},
	{1, std::make_tuple<>(mx::api::Step::g,5,0)},
	{2, std::make_tuple<>(mx::api::Step::g,5,1)},
	{3, std::make_tuple<>(mx::api::Step::a,5,0)},
	{4, std::make_tuple<>(mx::api::Step::b,5,-1)},
	{5, std::make_tuple<>(mx::api::Step::b,5,0)},
	{6, std::make_tuple<>(mx::api::Step::c,6,0)},
	{7, std::make_tuple<>(mx::api::Step::c,6,1)},
	{8, std::make_tuple<>(mx::api::Step::d,6,0)},
	{9, std::make_tuple<>(mx::api::Step::e,6,-1)},
	{10, std::make_tuple<>(mx::api::Step::e,6,0)},
	{11, std::make_tuple<>(mx::api::Step::f,6,0)},
};

std::unordered_map<int, std::pair<mx::api::DurationName, int>> rhythmLookUpTable{
	{1, std::make_pair<>(mx::api::DurationName::dur16th,0)},
	{2, std::make_pair<>(mx::api::DurationName::eighth,0)},
	{3, std::make_pair<>(mx::api::DurationName::eighth,1)},
	{4, std::make_pair<>(mx::api::DurationName::quarter,0)},
	{6, std::make_pair<>(mx::api::DurationName::quarter,1)},
	{7, std::make_pair<>(mx::api::DurationName::quarter,2)},
	{8, std::make_pair<>(mx::api::DurationName::half, 0)},
	{12, std::make_pair<>(mx::api::DurationName::half, 1)},
	{14, std::make_pair<>(mx::api::DurationName::half, 2)},
	{16, std::make_pair<>(mx::api::DurationName::whole, 0)},
	{24, std::make_pair<>(mx::api::DurationName::whole, 1)},
};

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

std::vector<std::vector<int>> calculatePartition(int num) {
	std::unordered_map<int, std::vector<std::vector<int>>> partitionMemoisation({ { 1,{{1}} } });
	std::vector<std::vector<int>> output{{{num}} };

	if (partitionMemoisation.contains(num)) 
	{
		return partitionMemoisation[num];
	}
	for (int i=1; i<num; i++)
	{
		int first = num - i;
		std::vector<std::vector<int>> prev = calculatePartition(i);
		for (std::vector<int> part : prev)
		{
			part.push_back(first);
			output.push_back(part);
		}
	}

	partitionMemoisation[num] = output;
	return output;
}

std::vector<int> randomPartition(int num)
{
	const long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::vector<std::vector<int>> partitions = calculatePartition(num);
	std::uniform_int_distribution<int> randomPartitionDistribution(0, partitions.size()-1);
	return partitions[randomPartitionDistribution(generator)]; //return a copy????
}

void rescale(std::vector<int>& vec, int scalar)
{
	for (int& element : vec)
	{
		element *= scalar;
	}
}

mx::api::NoteData createNote(int pitch, int duration, int tickCount, bool start, bool middle, bool end, bool no_altered)
{
	auto note = mx::api::NoteData{};
	auto noteInfo = chromaticScale.find(pitch)->second;

	note.pitchData.step = get<0>(noteInfo);
	note.pitchData.alter = get<2>(noteInfo);
	note.pitchData.octave = get<1>(noteInfo);

	if (get<2>(noteInfo)==-1)
	{
		note.pitchData.accidental = mx::api::Accidental::flat;

	} else if (get<2>(noteInfo))
	{
		note.pitchData.accidental = mx::api::Accidental::sharp;
	} else
	{
		note.pitchData.accidental = mx::api::Accidental::natural; //change natural!!!
	}

	if (no_altered)
	{
		note.pitchData.accidental = mx::api::Accidental::none;
	}

	auto durationInfo = rhythmLookUpTable.find(duration)->second;
	note.durationData.durationName = durationInfo.first;
	note.durationData.durationDots = durationInfo.second;
	note.tickTimePosition = tickCount;

	if (start)
	{
		note.beams.push_back(mx::api::Beam::begin);
	}
	if (middle)
	{
		note.beams.push_back(mx::api::Beam::extend);
	}
	if (end)
	{
		note.beams.push_back(mx::api::Beam::end);
	}

	return note;
}

 void addNoteToMeasure( mx::api::MeasureData* measureP, int pitch, int duration, int tickCount, bool start, bool middle, bool end, bool no_altered)
{
    using namespace mx::api;
    auto staffP = &measureP->staves.at(0);
    int voice = 0;
    staffP->voices[voice].notes.emplace_back(createNote(pitch,duration, tickCount, start, middle, end, no_altered));
}

 mx::api::MeasureData* addMeasure(mx::api::PartData& part)
{
    using namespace mx::api;
    part.measures.emplace_back(MeasureData{});
    auto measureP = &part.measures.back();
    measureP->staves.emplace_back(StaffData{});
	return measureP;
}

 mx::api::MeasureData* addFirstMeasure(mx::api::PartData& part, TimeSignature timeSignature)
{
    using namespace mx::api;
    part.measures.emplace_back(MeasureData{});
    auto measureP = &part.measures.front();
	measureP->timeSignature.beats = timeSignature.getNumerator();
	measureP->timeSignature.beatType = timeSignature.getDenominator();
    measureP->timeSignature.isImplicit = false;

    measureP->staves.emplace_back(StaffData{});
    auto staffP = &measureP->staves.at(0);
    staffP->clefs.emplace_back(ClefData{});
    auto clefP = &staffP->clefs.back();
    clefP->symbol = ClefSymbol::g;
    clefP->line = 2;

	return measureP;
}

 void adjustAlterationTable(std::vector<bool>& alt, int pitch)
 {
	 const std::unordered_set<int> naturals = { 1,3,5,6,8,10,11 };
	 const std::unordered_set<int> accidentals = { 0,2,4,7,9 };

	 const int pitch_corrected = (pitch % 12 >= 0) ? (pitch % 12) : ((pitch % 12) + 12);

	if (naturals.contains(pitch_corrected))
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
	} else
	{
		switch (pitch_corrected)
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

 bool alterationValueFromPitch(const std::vector<bool>& alt, int pitch)
 {

	const  std::unordered_set<int> naturals = { 1,3,5,6,8,10,11 };
	const  std::unordered_set<int> accidentals = { 0,2,4,7,9 };

	 const int pitch_corrected = (pitch % 12 >= 0) ? (pitch % 12) : ((pitch % 12) + 12);

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

 bool isAltered(int pitch)
 {
	 const  std::unordered_set<int> naturals = { 1,3,5,6,8,10,11 };
	 const  std::unordered_set<int> accidentals = { 0,2,4,7,9 };

	 const int pitch_corrected = (pitch % 12 >= 0) ? (pitch % 12) : ((pitch % 12) + 12);

	 if (naturals.contains(pitch_corrected))
	 {
		 return false;
	 }
	 return true;
 }
