#ifndef SCOREXML_H
#define SCOREXML_H
#include "mx/api/ScoreData.h"
#include "melody.h"

class ScoreXML
{
public:
	ScoreXML(Melody& melody, std::string&& title, std::string&& instrument);
	mx::api::ScoreData convertToXML();
private:
	mx::api::ScoreData score;
	Measure timeSignature;
	std::vector<std::pair<int, int>>  melody_array;

};

#endif // !SCOREXML_H
