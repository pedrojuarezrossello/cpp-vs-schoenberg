#ifndef TABLES_H
#define TABLES_H
#include <unordered_set>
#include <unordered_map>
#include <mx/api/DurationData.h>
#include <mx/api/PitchData.h>

using std::unordered_map;
using std::unordered_set;
using std::tuple;
using std::pair;
using std::make_tuple;
using std::make_pair;
using mx::api::Step;
using mx::api::DurationName;

const unordered_map<int, tuple<Step, int, int>> chromaticScale{
	{-11, make_tuple<>(Step::g,4,0)},
	{-10, make_tuple<>(Step::g,4,1)},
	{-9, make_tuple<>(Step::a,4,0)},
	{-8, make_tuple<>(Step::b,4,-1)},
	{-7, make_tuple<>(Step::b,4,0)},
	{-6, make_tuple<>(Step::c,5,0)},
	{-5, make_tuple<>(Step::c,5,1)},
	{-4, make_tuple<>(Step::d,5,0)},
	{-3, make_tuple<>(Step::e,5,-1)},
	{-2, make_tuple<>(Step::e,5,0)},
	{-1, make_tuple<>(Step::f,5,0)},
	{0, make_tuple<>(Step::f,5,1)},
	{1, make_tuple<>(Step::g,5,0)},
	{2, make_tuple<>(Step::g,5,1)},
	{3, make_tuple<>(Step::a,5,0)},
	{4, make_tuple<>(Step::b,5,-1)},
	{5, make_tuple<>(Step::b,5,0)},
	{6, make_tuple<>(Step::c,6,0)},
	{7, make_tuple<>(Step::c,6,1)},
	{8, make_tuple<>(Step::d,6,0)},
	{9, make_tuple<>(Step::e,6,-1)},
	{10, make_tuple<>(Step::e,6,0)},
	{11, make_tuple<>(Step::f,6,0)},
};

const unordered_map<int, pair<DurationName, int>> rhythmLookUpTable{
	{1, make_pair<>(DurationName::dur16th,0)},
	{2, make_pair<>(DurationName::eighth,0)},
	{3, make_pair<>(DurationName::eighth,1)},
	{4, make_pair<>(DurationName::quarter,0)},
	{6, make_pair<>(DurationName::quarter,1)},
	{7, make_pair<>(DurationName::quarter,2)},
	{8, make_pair<>(DurationName::half, 0)},
	{12, make_pair<>(DurationName::half, 1)},
	{14, make_pair<>(DurationName::half, 2)},
	{16, make_pair<>(DurationName::whole, 0)},
	{24, make_pair<>(DurationName::whole, 1)},
};

const unordered_set<int> naturals = { 1,3,5,6,8,10,11 };
const unordered_set<int> accidentals = { 0,2,4,7,9 };

#endif //TABLES_H
