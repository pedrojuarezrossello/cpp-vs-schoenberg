# C++ vs Schoenberg
This programme implements a randomised version of the twelve-tone technique as developed by Arnold Schoenberg in the first third of the 20th century. It revolves around the concept of a tone row, which is a particular permutation of the twelve tones in the chromatic scale, remaining fixed throughout the work. Four different types of transformations may be applied:

* Inversion: a melodic fragment is inverted by flipping it "upside-down", reversing the melody's contour. For instance, if the original melody has a rising major third, then the inverted melody has a falling major third.
* Retrograde: this is just playing the melody backwards, starting from the end.
* Retrograde-inversion: the retrograde of the inverse melody.
* Transposition: shift the entire melody by a pitch class (from 0 to 11 semitones).

To replicate a composer picking a row, we've just picked a random permutation from 0 to 11. Then, to generate the melodic contour, we section off groups of pitches of random length and perform one of the transformations above according to a randomised queuing system. 

However, this processes is subordinated to the rhythm schema, since obviously each pitch must be attached to a duration. To achieve a more musically-minded rhythm, we've subdivided each bar into a random partition (e.g. 4 = 1 + 2 + 1 would be crotchet minim crotchet), and then sequentially through this partition we subdivide even further in  BFS manner, though not always as we might stop early due to some random parmeters.

To construct the XML, we use a library mainly developed by Matt James Briggs (https://github.com/webern), which can be cloned here: https://github.com/webern/mx/tree/master. It'll be necessary for you to run the programme. 

To install the programme into your preferred environment, you should simply do 
```
git clone https://github.com/pedrojuarezrossello/cpp-vs-schoenberg.git 
cd cpp-vs-schoenberg/schoenberg
cmake .
```

Then running the following code will generate a music XML file in your directory which you can visualise in webistes like https://www.soundslice.com/musicxml-viewer/:

```
#include "include/score.h"

int main() {

  //the template parameters are the time signature (note second can only be 4 or 8)
  //the first argument is the title
  //the second the instrument
  //the third the number of bars
   ScoreXML<4,4> scoreXml("Test", "Violin", 4); 

  //convert to ScoreData format (mx library)
   scoreXml.convertToXML();

  //writes the file to the filepath in the second argument, and if the third is true, also to the console
   writeMusicXMLFile<>(scoreXml, "../output.musicxml", true);

	return 0;
}
```
