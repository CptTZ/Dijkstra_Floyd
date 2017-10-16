/**
 * Dijkstra Algorithm
 */

#include "dijkstra.h"


void dij_2d(Graph g, int src, int end, int** path, int* distance, BOOL* final)
{
}

double dijkstra(Graph g, char* source, char* target, Result* result)
{
    if (&g == NULL) return -1;
    int idx_src = find_index_by_vertex_name(g, source),
        idx_end = find_index_by_vertex_name(g, target);
    if (idx_end < 0 || idx_src < 0)
    {
        puts("Input vertex not found");
        return -1;
    }

    int **path = malloc(g.vertex_count * SIZE_POINTER_1), *distance = malloc(g.vertex_count * SIZE_INT);
    BOOL* final = malloc(g.vertex_count * SIZE_CHAR);

    clock_t start = get_current_clock();

    if (g.type == 0)
    {
        dij_2d(g, idx_src, idx_end, path, distance, final);
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
