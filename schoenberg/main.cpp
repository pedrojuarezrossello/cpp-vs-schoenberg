#include <chrono>
#include "include/score.h"
#include "mx/api/ScoreData.h"
#include "include/utils/utils.h"

int main() {

   ScoreXML<3,4> scoreXml("Test", "Violin", 2);

   scoreXml.convertToXML();
   const auto score = scoreXml.getScore();

   writeMusicXMLFile(score, "../output.musicxml", true);

	return 0;
}
