/**
 * Floyd-Warshall Algorithm
 */

#include "floyd.h"



double floyd(Graph g, char* source, char* target, Result *result)
{
    if (&g == NULL) return -1;
    int idx_src = find_index_by_vertex_name(g, source),
        idx_end = find_index_by_vertex_name(g, target);
    if (idx_end<0 || idx_src<0)
    {
        puts("Input vertex not found");
        return -1;
    }

    clock_t start = get_current_clock();

    if (g.type == 0)
    {
    }
    else if (g.type == 1)
    {
    }
    else if (g.type == 2)
    {
    }
    else return -1;

    clock_t end = get_current_clock();

    result = malloc(SIZE_RESULT);


    return clock_to_ms(end, start);
}
