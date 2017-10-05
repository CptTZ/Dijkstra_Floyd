/**
 * Some tools for this project
 */

#include "tools.h"

int nextRndInt(int upper)
{
    // Reference: https://stackoverflow.com/a/13520000
    int rnd = (int)(upper * (rand() / (RAND_MAX + 1.0)));
    return 1 + rnd;
}

clock_t getCurrentClock()
{
    return clock();
}

double clockToMs(const clock_t stop, const clock_t start)
{
    return (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
}
