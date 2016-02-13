#include <stdio.h>
#include <map>
#include "map_iterators.h"

typedef std::map<const char*, int> Scores;


void PrintScores(const Scores& scores)
{
    for (const auto& key : key_range_const(scores))
    {
        printf("key = %s\n", key);
    }
    for (const auto& value : value_range_const(scores))
    {
        printf("value = %d\n", value);
    }
}

void MutateScores(Scores& scores)
{
    for (auto& value : value_range(scores))
    {
        value += 1;
        printf("value = %d\n", value);
    }
}


int main()
{
    Scores scores;
    scores["AAA"] = 100;
    scores["BBB"] = 90;
    scores["CCC"] = 80;

    PrintScores(scores);
    MutateScores(scores);

    return 0;
}
