#include <iostream>
#include "melody.h"
#include "ScoreXML.h"
#include "utils.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include "mx/api/PartData.h"
#include "mx/api/MeasureData.h"
#include "mx/api/StaffData.h"
#include "mx/api/ClefData.h"
#include "mx/api/VoiceData.h"
#include "mx/api/NoteData.h"
#include "mx/api/DurationData.h"
#include "mx/api/PitchData.h"


#define MX_WRITE_THIS_TO_THE_CONSOLE 1

int main() {

    TimeSignature<4, 4> timeSignature;
    std::cout << timeSignature.getDenominator();

	//Melody melody(12, timeSignature);

    /*auto vec = melody.generate();

    for (auto a : vec)
    {
        std::cout << '(' << a.first << ',' << a.second << ')' << " ";
    }*/

  /* ScoreXML scoreXml(melody, "Test", "Violin");

   auto score = scoreXml.convertToXML();
    
    // the document manager is the liaison between our score data and the MusicXML DOM.
    // it completely hides the MusicXML DOM from us when using mx::api
    auto& mgr = mx::api::DocumentManager::getInstance();
    const auto documentID = mgr.createFromScore(score);

    // write to the console
#if MX_WRITE_THIS_TO_THE_CONSOLE
    mgr.writeToStream(documentID, std::cout);
    std::cout << std::endl;
#endif

    // write to a file
    mgr.writeToFile(documentID, "../output.musicxml");

    // we need to explicitly delete the object held by the manager
    mgr.destroyDocument(documentID);
    */

	return 0;
}
