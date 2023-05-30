#include <iostream>
#include "ScoreXML.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"

#define MX_WRITE_THIS_TO_THE_CONSOLE 1

int main() {

   ScoreXML<3,4> scoreXml("Test", "Violin", 12);

   scoreXml.convertToXML();
   const auto score = scoreXml.getScore();

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
    

	return 0;
}
