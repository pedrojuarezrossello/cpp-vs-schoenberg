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

   Measure timeSignature(3, 4);
    Melody melody(4, timeSignature);
   /* auto vec = melody.generate();

    for (auto a : vec)
    {
        std::cout << '(' << a.first << ',' << a.second << ')' << " ";
    }*/

   ScoreXML scoreXml(melody, "Test", "Violin");

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

    /*using namespace mx::api;
    const auto qticks = 4;

    // create a score
    auto score = ScoreData{};
    score.workTitle = "Mx Example";
    score.composer = "Matthew James Briggs";
    score.copyright = "Copyright (c) 2019";
    score.ticksPerQuarter = qticks;

    // create a part
    score.parts.emplace_back(PartData{});
    auto& part = score.parts.back();

    // give the part a name
    part.name = "Flute";
    part.abbreviation = "Fl.";
    part.displayName = "Flute";
    part.displayAbbreviation = "Fl.";

    // give the part an instrument
    part.instrumentData.soundID = SoundID::windFlutesFlute;
    part.instrumentData.midiData.channel = 1;
    part.instrumentData.midiData.program = 74;

    // add a measure
    part.measures.emplace_back(MeasureData{});
    auto& measure = part.measures.back();
    measure.timeSignature.beats = 4;
    measure.timeSignature.beatType = 4;
    measure.timeSignature.isImplicit = false;

    // add a staff
    measure.staves.emplace_back(StaffData{});
    auto& staff = measure.staves.back();

    // set the clef
    auto clef = ClefData{};
    clef.setTreble();
    staff.clefs.emplace_back(clef);

    // add a voice
    staff.voices[0] = VoiceData{};
    auto& voice = staff.voices.at(0);

    const auto quarter = qticks;
    const auto half = qticks * 2;
    const auto eighth = qticks / 2;

    // add a few notes
    auto currentTime = 0;
    auto note = NoteData{};
    note.pitchData.step = Step::d;
    note.pitchData.alter = 1;
    note.pitchData.octave = 5;
    note.pitchData.accidental = Accidental::sharp;
    note.durationData.durationName = DurationName::half;
    note.durationData.durationTimeTicks = half;
    note.isTieStart = true;
    note.tickTimePosition = currentTime;
    voice.notes.push_back(note);

    // advance our time
    currentTime += half;
    note.pitchData.step = Step::d;
    note.pitchData.alter = 1;
    note.pitchData.octave = 5;
    note.pitchData.accidental = Accidental::sharp;
    note.durationData.durationName = DurationName::eighth;
    note.durationData.durationTimeTicks = eighth;
    note.isTieStart = false;
    note.isTieStop = true;
    note.tickTimePosition = currentTime;
    // beams are handled explicitly in mus// start an eighth-note beam
    voice.notes.push_back(note);

    currentTime += eighth;

    note.pitchData.step = Step::e;
    note.pitchData.alter = 0;
    note.pitchData.octave = 5;
    note.pitchData.accidental = Accidental::none;
    note.durationData.durationName = DurationName::eighth;
    note.tickTimePosition = currentTime;
    note.isTieStart = false;
    note.isTieStop = false;
    note.durationData.durationTimeTicks = eighth;
     // end the eighth-note beam
    voice.notes.push_back(note);

    auto& mgr = DocumentManager::getInstance();
    const auto documentID = mgr.createFromScore(score);

    // write to the console
#if MX_WRITE_THIS_TO_THE_CONSOLE
    mgr.writeToStream(documentID, std::cout);
    std::cout << std::endl;
#endif

    // write to a file
    mgr.writeToFile(documentID, "./example.musicxml");

    // we need to explicitly delete the object held by the manager
    mgr.destroyDocument(documentID);
    */

	return 0;
}
