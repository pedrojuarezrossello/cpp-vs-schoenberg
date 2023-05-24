#include "ScoreXML.h"

#include "utils.h"

ScoreXML::ScoreXML(Melody& melody, std::string&& title, std::string&& instrument) : score(mx::api::ScoreData{}), timeSignature(melody.getMeasure()), melody_array(std::vector<std::pair<int, int>>())
{
    //set title
	score.workTitle = title;

    // create a part
    score.parts.emplace_back(mx::api::PartData{});
    auto part = score.parts.back();

    // give the part a name
    part.name = instrument;

    //generate melody vector
    melody_array = melody.generate();
}


mx::api::ScoreData ScoreXML::convertToXML()
{
    int semiQuaverCount{ 0 };
    const int semiQuaversPerBar = (timeSignature.getDenominator() == 4) ? (timeSignature.getNumerator() * 4) : (timeSignature.getNumerator() * 2);
    const int semiQuaversPerBeat = (timeSignature.getDenominator() == 4) ? 4 : 6;
    auto& part = score.parts.back();
    auto bar = addFirstMeasure(part,timeSignature);
    int semiQuaverCountPerBeat{ 0 };

    for (auto pair : melody_array)
    {
        bool isStartBeam{ false };
        bool isContinuingBeam{ false };
        bool isEndBeam{ false };

        if (pair.second >= 4)
        {
            addNoteToMeasure(bar, pair.first, pair.second, semiQuaverCount,false,false,false);
            semiQuaverCountPerBeat = pair.second % semiQuaversPerBeat;
        }
        else if (semiQuaverCountPerBeat == 0)
        {
            addNoteToMeasure(bar, pair.first, pair.second, semiQuaverCount,true,false,false);
            semiQuaverCountPerBeat += pair.second;
        } 
        else if (semiQuaverCountPerBeat > 0 && pair.second + semiQuaverCountPerBeat < semiQuaversPerBeat)
        {
            addNoteToMeasure(bar, pair.first, pair.second, semiQuaverCount,false,true,false);
            semiQuaverCountPerBeat += pair.second;
        }
        else if (semiQuaverCountPerBeat > 0 && pair.second + semiQuaverCountPerBeat == semiQuaversPerBeat)
        {
            addNoteToMeasure(bar, pair.first, pair.second, semiQuaverCount,false,false,true);
            semiQuaverCountPerBeat = 0;
        } else if (semiQuaverCountPerBeat > 0 && pair.second + semiQuaverCountPerBeat > semiQuaversPerBeat)
        {
            addNoteToMeasure(bar, pair.first, pair.second, semiQuaverCount, false, false, false);
            semiQuaverCountPerBeat = (semiQuaverCountPerBeat + pair.second) % semiQuaversPerBeat;
        }

        semiQuaverCount += pair.second;
        if (semiQuaverCount == semiQuaversPerBar)
        {
            bar = addMeasure(part);
            semiQuaverCount = 0;
        }
    }

    part.measures.pop_back();

    return score;
}

