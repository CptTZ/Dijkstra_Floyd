/**
 * Floyd-Warshall Algorithm
 */

#include "floyd.h"

int** floyd_2d(Graph g, int** floyd_path)
{
    int vex_count = g.vertex_count;
    int** g_matrix = g.adjacent.matrix_2d;
    int** ans = malloc(vex_count * SIZE_POINTER_1);

    // Copy the graph's adjacent matrix and init the path
    for (int i = 0; i < vex_count; ++i)
    {
        ans[i] = malloc(vex_count * SIZE_INT);
        for (int j = 0; j < vex_count; ++j)
        {
            ans[i][j] = g_matrix[i][j];
            floyd_path[i][j] = j;
        }
    }

    // Keep comparing all nodes
    for (int i = 0; i < vex_count; ++i)
    {
        for (int j = 0; j < vex_count; ++j)
        {
            for (int k = 0; k < vex_count; ++k)
            {
                int possible_short = ans[j][i] + ans[i][k];
                if (possible_short < ans[j][k])
                {
                    ans[j][k] = possible_short;
                    floyd_path[j][k] = floyd_path[j][i];
                }
            }
        }
    }

    return ans;
}

// Restore path by vertex index
int* gen_path_f(int** floyd_path, int src, int end, int count_vertex)
{
    if (floyd_path[src][end] == -1) return "No path found!\n";
    int* path_info = malloc(count_vertex * SIZE_INT);
    // Initialize the path info with -1 path
    for (int i = 0; i < count_vertex; ++i)
    {
        path_info[i] = -1;
    }
    int aux_i = 0;

    path_info[0] = src; // First node is src
    while (src != end)
    {
        src = floyd_path[src][end];
        path_info[++aux_i] = src;
    }
    return path_info;
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

    int count_vex = g.vertex_count;
    int **floyd_answer = NULL,
        **floyd_path = malloc(count_vex * SIZE_POINTER_1); // Special array to store path info
    for (int i = 0; i < count_vex; ++i)
    {
        floyd_path[i] = malloc(count_vex * SIZE_INT);
        for (int j = 0; j < count_vex; ++j)
        {
            floyd_path[i][j] = -1; // Get rid of no path
        }
    }

    // Below are true algorithm time
    clock_t start = get_current_clock();

    if (g.type == 0)
    {
        floyd_answer = floyd_2d(g, floyd_path);
    }
    else if (g.type == 1)
    {
    }
    else if (g.type == 2)
    {
    }
    else return -1;

    result->total_weight = floyd_answer[idx_src][idx_end];
    if (result->total_weight >= 0) // There is a path
    {
        int* path_info = gen_path_f(floyd_path, idx_src, idx_end, count_vex);
        char** final_route = calloc(count_vex, SIZE_POINTER_1);
        for (int i = 0; i < count_vex; ++i)
        {
            int idx = path_info[i];
            if (idx == -1) continue;
            final_route[i] = find_vertex_name_by_index(g, idx);
        }

        result->route = final_route;
        free(path_info);
    }

    clock_t end = get_current_clock();
    // Above are true algorithm time

    // free tmp vars 'gen_path' 'floyd_answer' 'floyd_path'
    for (int i = 0; i < count_vex; ++i)
    {
        free(floyd_answer[i]);
        free(floyd_path[i]);
    }
    free(floyd_path);
    free(floyd_answer);

    return clock_to_ms(end, start);
}
