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
    int semiQuaverCount{ 0 };
    const int semiQuaversPerBar = (time_signature.getDenominator() == 4) ? (time_signature.getNumerator() * 4) : (time_signature.getNumerator() * 2);
    const int semiQuaversPerBeat = (time_signature.getDenominator() == 4) ? 4 : 6;
    auto& part = score.parts.back();
	auto bar = addFirstMeasure(part, time_signature.getNumerator(), time_signature.getDenominator());
    int semiQuaverCountPerBeat{ 0 };
    std::vector<bool> alt(7, false);

    for (const auto[pitch,duration] : melody_array)
    {

        bool no_alteration{ false };

        if ((!isAltered(pitch) && !alterationValueFromPitch(alt, pitch)) || (isAltered(pitch) && alterationValueFromPitch(alt,pitch)))
        {
            no_alteration = true;
        }

        adjustAlterationTable(alt, pitch);

        if (duration >= 4)
        {
            addNoteToMeasure(bar, pitch, duration, semiQuaverCount, false, false, false, no_alteration);
            semiQuaverCountPerBeat = (semiQuaverCountPerBeat + duration) % semiQuaversPerBeat;
        }
        else if (semiQuaverCountPerBeat == 0)
        {
            addNoteToMeasure(bar, pitch, duration, semiQuaverCount, true, false, false, no_alteration);
            semiQuaverCountPerBeat += duration;
        }
        else if (semiQuaverCountPerBeat > 0 && duration + semiQuaverCountPerBeat < semiQuaversPerBeat)
        {
            addNoteToMeasure(bar, pitch, duration, semiQuaverCount, false, true, false, no_alteration);
            semiQuaverCountPerBeat += duration;
        }
        else if (semiQuaverCountPerBeat > 0 && duration + semiQuaverCountPerBeat == semiQuaversPerBeat)
        {
            addNoteToMeasure(bar, pitch, duration, semiQuaverCount, false, false, true, no_alteration);
            semiQuaverCountPerBeat = 0;
        }
        else if (semiQuaverCountPerBeat > 0 && duration + semiQuaverCountPerBeat > semiQuaversPerBeat)
        {
            addNoteToMeasure(bar, pitch, duration, semiQuaverCount, false, false, false, no_alteration);
            semiQuaverCountPerBeat = (semiQuaverCountPerBeat + duration) % semiQuaversPerBeat;
        }

        semiQuaverCount += duration;
        if (semiQuaverCount == semiQuaversPerBar)
        {
            bar=addMeasure(part);
            semiQuaverCount = 0;
            alt = { false,false,false,false,false,false,false };
        }
    }

    part.measures.pop_back();

}


#endif // !SCOREXML_H
