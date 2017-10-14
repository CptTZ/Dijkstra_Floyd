/**
 * Some tools for this project
 */

#include "tools.h"

int next_rnd_int(int upper)
{
    int rnd = (int)(upper * (rand() / (RAND_MAX + 1.0)));
    return rnd + 1;
}

clock_t get_current_clock()
{
    return clock();
}

double clock_to_ms(const clock_t stop, const clock_t start)
{
    return (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
}
