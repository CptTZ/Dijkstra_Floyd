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

void dij_list(Graph g, int idx_target, int* path, int* distance, BOOL* prev)
{
    int v_cout = g.vertex_count;

    // Find every shortest path starts from src
    for (int i = 0; i < v_cout; ++i)
    {
        int min_idx = min_dist_current_vertex(v_cout, distance, prev);
        int curr_distance = distance[min_idx];
        prev[min_idx] = TRUE;

        // Already found the shortest path
        // Not doing all-pairs for now
        if (min_idx == idx_target) break;

        // Do the 'distance value' update iteration
        for (int j = 0; j < v_cout; ++j)
        {
            int current_vertex_weight =
                get_node_weight_in_graph_list_by_index(g, min_idx, j);
            // Not found is not connected
            if (current_vertex_weight == -1) current_vertex_weight = INT_AS_INFI;

            int possible_next_distance = curr_distance + current_vertex_weight;
            if (prev[j] == FALSE
                && current_vertex_weight != 0
                && curr_distance != INT_AS_INFI
                && possible_next_distance < distance[j])
            {
                distance[j] = possible_next_distance;
                path[j] = min_idx;
            }
        }
    }
}

void dij_1d(Graph g, int idx_target, int* path, int* distance, BOOL* prev)
{
    int v_cout = g.vertex_count,
        *g_matrix = g.adjacent.matrix_1d;

    // Find every shortest path starts from src
    for (int i = 0; i < v_cout; ++i)
    {
        int min_idx = min_dist_current_vertex(v_cout, distance, prev);
        int curr_distance = distance[min_idx];
        prev[min_idx] = TRUE;

        // Already found the shortest path
        // Not doing all-pairs for now
        if (min_idx == idx_target) break;

        // Do the 'distance value' update iteration
        for (int j = 0; j < v_cout; ++j)
        {
            // Flatten the 2D index to 1D index
            int ii = min_idx, jj = j;
            if (ii < jj)
            {
                ii ^= jj;
                jj ^= ii;
                ii ^= jj;
            }
            // Lower triangle trick
            int new_idx = ii * (ii + 1) / 2 + jj,
                possible_next_distance = curr_distance + g_matrix[new_idx];

            if (prev[j] == FALSE
                && g_matrix[new_idx] != 0
                && curr_distance != INT_AS_INFI
                && possible_next_distance < distance[j])
            {
                distance[j] = possible_next_distance;
                path[j] = min_idx;
            }
        }
    }
}

void dij_2d(Graph g, int idx_target, int* path, int* distance, BOOL* prev)
{
    int v_cout = g.vertex_count,
        **g_matrix = g.adjacent.matrix_2d;

    // Find every shortest path starts from src
    for (int i = 0; i < v_cout; ++i)
    {
        int min_idx = min_dist_current_vertex(v_cout, distance, prev);
        int curr_distance = distance[min_idx];
        prev[min_idx] = TRUE;

        // Already found the shortest path
        // Not doing all-pairs for now
        if (min_idx == idx_target) break;

        // Do the 'distance value' update iteration
        for (int j = 0; j < v_cout; ++j)
        {
            int possible_next_distance = curr_distance + g_matrix[min_idx][j];
            if (prev[j] == FALSE
                && g_matrix[min_idx][j] != 0
                && curr_distance != INT_AS_INFI
                && possible_next_distance < distance[j])
            {
                distance[j] = possible_next_distance;
                path[j] = min_idx;
            }
        }
    }
}

int* gen_path_d(int* path, int src, int end, int count_vertex)
{
    int* path_info = malloc(count_vertex * SIZE_INT);
    // Initialize the path info with -1 path
    for (int i = 0; i < count_vertex; ++i)
    {
        path_info[i] = -1;
    }

    int aux_i = 0;
    // It's actually in reverse
    for (int i = end; path[i] != -1; aux_i++)
    {
        path_info[count_vertex - 1 - aux_i] = i;
        i = path[i];
    }

    // Potential problem: path_info have some blank
    path_info[0] = src;
    return path_info;
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

    int *path = malloc(vertex_count * SIZE_INT), // Path description for final answers
        *distance = malloc(vertex_count * SIZE_INT); // The shortest path from source to target
    BOOL* previous_state = malloc(vertex_count * SIZE_CHAR); // Is the one vertex in the distance array?

    // Below are true algorithm time
    clock_t start = get_current_clock();

    // Initialize
    for (int i = 0; i < vertex_count; ++i)
    {
        path[i] = -1;
        distance[i] = INT_AS_INFI;
        previous_state[i] = FALSE;
    }
    // However, distance to self must be 0
    distance[idx_src] = 0;

    // Calculation based on Graph's type
    if (g.type == 0)
    {
        dij_2d(g, idx_end, path, distance, previous_state);
    }
    else if (g.type == 1)
    {
        dij_1d(g, idx_end, path, distance, previous_state);
    }
    else if (g.type == 2)
    {
        dij_list(g, idx_end, path, distance, previous_state);
    }
    else return -1;

    result->no_output = FALSE;
    result->resolver = "dijkstra";
    result->total_weight = distance[idx_end];
    if (result->total_weight >= 0)
    {
        int* path_info = gen_path_d(path, idx_src, idx_end, vertex_count);
        char** final_route = calloc(vertex_count, SIZE_POINTER_1);
        for (int i = 0, aux_i = 0; i < vertex_count; ++i)
        {
            int idx = path_info[i];
            if (idx == -1) continue;
            final_route[aux_i++] = find_vertex_name_by_index(g, idx);
        }
        result->route = final_route;
        free(path_info);
    }

    clock_t end = get_current_clock();
    // Above are true algorithm time

    // Free tmp vars
    free(previous_state);
    free(path);
    free(distance);

    return clock_to_ms(end, start);
}
