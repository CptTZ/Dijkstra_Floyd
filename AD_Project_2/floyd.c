/**
 * Floyd-Warshall Algorithm
 */

#include "floyd.h"

int** floyd_2d(Graph g)
{
    int vex_count = g.vertex_count;
    int** g_matrix = g.adjacent.matrix_2d;
    int** ans = malloc(vex_count * SIZE_POINTER_1);

    // Copy the graph's adjacent matrix
    for (int i = 0; i < vex_count; ++i)
    {
        ans[i] = malloc(vex_count * SIZE_INT);
        for (int j = 0; j < vex_count; ++j)
        {
            ans[i][j] = g_matrix[i][j];
        }
    }

    for (int i = 0; i < vex_count; ++i)
    {
        for (int j = 0; j < vex_count; ++j)
        {
            for (int k = 0; k < vex_count; ++k)
            {
                int possible_short = ans[j][i] + ans[i][k];
                if (possible_short < ans[j][k])
                    ans[j][k] = possible_short;
            }
        }
    }

    return ans;
}

double floyd(Graph g, char* source, char* target, Result* result)
{
    if (&g == NULL) return -1;
    int idx_src = find_index_by_vertex_name(g, source),
        idx_end = find_index_by_vertex_name(g, target);
    if (idx_end < 0 || idx_src < 0)
    {
        puts("Input vertex not found");
        return -1;
    }

    int** floyd_answer;

    // Below are true algorithm time
    clock_t start = get_current_clock();

    if (g.type == 0)
    {
        floyd_answer = floyd_2d(g);
    }
    else if (g.type == 1)
    {
    }
    else if (g.type == 2)
    {
    }
    else return -1;

    clock_t end = get_current_clock();

    //TODO: Generate Final Printable Result Here


    return clock_to_ms(end, start);
}
