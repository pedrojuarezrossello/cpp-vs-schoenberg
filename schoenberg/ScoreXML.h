#ifndef SCOREXML_H
#define SCOREXML_H
#include "mx/api/ScoreData.h"
#include "include/score_utils.h"
#include "melody.h"

using std::vector;
using std::string;
using std::pair;
using mx::api::ScoreData;
using mx::api::PartData;


template<int Numerator, int Denominator>
class ScoreXML
{
public:
	ScoreXML( string&& title, string&& instrument, int number_of_bars);
	ScoreXML(const string& title, const string& instrument, int number_of_bars);
    ScoreData getScore() { return score; }
	void convertToXML();
private:
	ScoreData score;
	TimeSignature<Numerator,Denominator> time_signature;
	vector<pair<int, int>>  melody_array;
};

template<int Numerator, int Denominator>
ScoreXML<Numerator, Denominator>::ScoreXML(string&& title, string&& instrument, int number_of_bars) : score(ScoreData{}), time_signature(TimeSignature<Numerator, Denominator>()), melody_array(vector<pair<int, int>>())
{
    //set title
    score.workTitle = title;

    // create a part
    score.parts.emplace_back(PartData{});
    auto part = score.parts.back();

    // give the part a name
    part.name = instrument;

    //create a melody instance
    auto melody = Melody<Numerator, Denominator>(number_of_bars);

    //generate melody vector
    melody_array = melody.generate();
}

template<int Numerator, int Denominator>
ScoreXML<Numerator, Denominator>::ScoreXML(const string& title, const string& instrument, int number_of_bars) : score(ScoreData{}), time_signature(TimeSignature<Numerator, Denominator>()), melody_array(vector<pair<int, int>>())
{
    //set title
    score.workTitle = title;

    // create a part
    score.parts.emplace_back(PartData{});
    auto part = score.parts.back();

    // give the part a name
    part.name = instrument;

    //create a melody instance
    auto melody = Melody<Numerator, Denominator>(time_signature, number_of_bars);

    //generate melody vector
    melody_array = melody.generate();
}

template<int Numerator, int Denominator>
void ScoreXML<Numerator, Denominator>::convertToXML()
{
    //get part 
    auto& part = score.parts.back();
    //add first measure
	auto bar = addFirstMeasure(part, time_signature.getNumerator(), time_signature.getDenominator());
  
    //intialise trackers and alteration array
    int semiQuaverCount{ 0 };
    const int semiQuaversPerBar = (time_signature.getDenominator() == 4) ? (time_signature.getNumerator() * 4) : (time_signature.getNumerator() * 2);
    const int semiQuaversPerBeat = (time_signature.getDenominator() == 4) ? 4 : 6;
    int semiQuaverCountPerBeat{ 0 };
    vector<bool> alterations(7, false);

    for (const auto[pitch,duration] : melody_array)
    {
        //determine if we need to add an accidental to the note
        bool no_alteration{ false };

        //either it hasn't been altered yet and it is a natural OR it's been altered and the next occurence is also altered (so no need for accidental)
        if ((!isAltered(pitch) && !alterationValueFromPitch(alterations, pitch)) || (isAltered(pitch) && alterationValueFromPitch(alterations,pitch)))
        {
            no_alteration = true;
        }

        //update table
        adjustAlterationTable(alterations, pitch);

        //place the beams
        if (duration >= 4) //if it's a crotchet or longer then no beam
        {
            addNoteToMeasure(bar, pitch, duration, semiQuaverCount, BeamPosition::NO_BEAM, no_alteration);
            semiQuaverCountPerBeat = (semiQuaverCountPerBeat + duration) % semiQuaversPerBeat;
        }
        else if (semiQuaverCountPerBeat == 0) //start of the beam
        {
            addNoteToMeasure(bar, pitch, duration, semiQuaverCount, BeamPosition::START, no_alteration);
            semiQuaverCountPerBeat += duration;
        }
        else if (semiQuaverCountPerBeat > 0 && duration + semiQuaverCountPerBeat < semiQuaversPerBeat) /*a beam has started, and we haven't reached 
																											the end of the beat*/
        {
            addNoteToMeasure(bar, pitch, duration, semiQuaverCount, BeamPosition::MIDDLE, no_alteration); 
            semiQuaverCountPerBeat += duration;
        }
        else if (semiQuaverCountPerBeat > 0 && duration + semiQuaverCountPerBeat == semiQuaversPerBeat) //end of the beat and thus of beam
        {
            addNoteToMeasure(bar, pitch, duration, semiQuaverCount, BeamPosition::END, no_alteration);
            semiQuaverCountPerBeat = 0;
        }
        else if (semiQuaverCountPerBeat > 0 && duration + semiQuaverCountPerBeat > semiQuaversPerBeat) //beat overflow
        {
            addNoteWithTie(bar, pitch, semiQuaversPerBeat - semiQuaverCountPerBeat, duration, semiQuaverCount, semiQuaverCountPerBeat, no_alteration);
            semiQuaverCountPerBeat = (semiQuaverCountPerBeat + duration) % semiQuaversPerBeat;
        }

        semiQuaverCount += duration; //update the semiquaver count per bar
        if (semiQuaverCount == semiQuaversPerBar) //end of bar - update trackers
        {
            bar = addMeasure(part);
            semiQuaverCount = 0;
            alterations = vector<bool>(7,false);
        }
    }

    part.measures.pop_back(); //remove last measure (added in last iteration)

}


#endif // !SCOREXML_H
