#include <stdio.h>
#include <map>
#include "map_iterators.h"

typedef std::map<const char*, int> Scores;


void PrintScores(const Scores& scores)
{
    for (const auto& key : keys(scores))
    {
        printf("key = %s\n", key);
    }
    for (const auto& value : values(scores))
    {
        printf("value = %d\n", value);
    }
}

void MutateScores(Scores& scores)
{
    for (auto& key : keys(scores))
    {
        // NOTE: mutating key violates std::map's invariants, but
        // map's own iterator provides non-const access to key!
        printf("key = %s\n", key);
    }
    for (auto& value : values(scores))
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
