/**
 * Dijkstra Algorithm
 */

#include "dijkstra.h"

// Find the minimum distance for calculated vertex shortest path
int min_dist_current_vertex(int vertex_count, int* dist, BOOL* final)
{
    int min = INT_AS_INFI, min_idx = -1;

    for (int i = 0; i < vertex_count; i++)
    {
        if (final[i] == FALSE && dist[i] <= min)
        {
            min = dist[i];
            min_idx = i;
        }
    }

    return min_idx;
}

void dij_2d(Graph g, int** path, int* distance, BOOL* final)
{
    int v_cout = g.vertex_count,
        **g_matrix = g.adjacent.matrix_2d;
    // Find every shortest path starts from src
    for (int i = 0; i < v_cout - 1; ++i)
    {
        int min_idx = min_dist_current_vertex(v_cout, distance, final);
        final[min_idx] = TRUE;
        int curr_distance = distance[min_idx];

        // Do the 'distance value' update iteration
        for (int j = 0; j < v_cout; ++j)
        {
            int possible_next_distance = curr_distance + g_matrix[min_idx][j];
            if (final[j] == FALSE
                && g_matrix[min_idx][j] != 0
                && curr_distance != INT_AS_INFI
                && possible_next_distance < distance[j])
            {
                distance[j] = possible_next_distance;
            }
        }
    }
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

    int vertex_count = g.vertex_count;

    int **path = malloc(vertex_count * SIZE_POINTER_1), // Path description for final answers
        *distance = malloc(vertex_count * SIZE_INT); // The shortest path from source to target
    BOOL* final = malloc(vertex_count * SIZE_CHAR); // Is the one vertex in the distance array?

    // Below are true algorithm time
    clock_t start = get_current_clock();

    // Initialize
    for (int i = 0; i < vertex_count; ++i)
    {
        distance[i] = INT_AS_INFI;
        final[i] = FALSE;
    }
    // However, distance to self must be 0
    distance[idx_src] = 0;

    // Calculation based on Graph's type
    if (g.type == 0)
    {
        dij_2d(g, path, distance, final);
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

    //TODO: Free malloced space -> path, distance, final

    return clock_to_ms(end, start);
}
