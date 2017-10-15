/**
 * General Graph related functions
 */

#include "graph.h"
#include <limits.h>

Graph* create_graph_from_file(char* path)
{
    char* file_data = read_file_content(path);
    Graph* g = malloc(SIZE_GRAPH);
    g->type = 0;

    unsigned int lines = 1;
    // count lines in order to make array
    for (int i = 0; file_data[i] != '\0'; ++i)
    {
        if (file_data[i] == '\n') lines++;
    }
    g->vertex_count = lines;

    // Malloc 2D array and prep vertex names
    g->adjacent.matrix_2d = malloc(lines * SIZE_POINTER);
    g->vertex_names = malloc(lines * SIZE_POINTER);
    for (int i = 0; i < lines; ++i)
    {
        g->adjacent.matrix_2d[i] = malloc(lines * SIZE_INT);
        char* tmp_name = malloc(2);
        tmp_name[0] = 'A' + i;
        tmp_name[1] = '\0';
        g->vertex_names[i] = tmp_name;
    }

    // Read weight and build the graph
    int current_line = 0, current_col = 0, j, weight;
    for (int i = 0; file_data[i] != '\0'; ++i)
    {
        switch (file_data[i])
        {
        case ' ':
            break;
        case '\n':
            current_line++;
            current_col = 0;
            break;
        case '.':
            g->adjacent.matrix_2d[current_line][current_col++] = INT_MAX;
            break;
        default:
            // It's weight now
            for (j = i, weight = 0; file_data[j] >= '0' && file_data[j] <= '9'; ++j)
            {
                weight = weight * 10 + file_data[j] - '0';
            }
            g->adjacent.matrix_2d[current_line][current_col++] = weight;
            i = j - 1;
            break;
        }
    }

    free(file_data);
    return g;
}

int print_graph(Graph* g)
{
    int ll = g->vertex_count;
    switch (g->type)
    {
    case 0:
        for (int i = 0; i < ll; ++i)
        {
            for (int j = 0; j < ll; ++j)
            {
                int w = g->adjacent.matrix_2d[i][j];
                if (w == INT_MAX)
                    printf(" . ");
                else
                    printf("%4d", w);
            }
            putchar('\n');
        }
        break;
    case 1:
        for (int i = 0; i < ll; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                int w = g->adjacent.matrix_1d[i + j];
                if (w == INT_MAX)
                    printf(" . ");
                else
                    printf("%4d", w);
            }
            putchar('\n');
        }
        break;
    case 2:
        for (int i = 0; i < ll; ++i)
        {
            printf("%s: ", g->vertex_names[i]);
            struct _link_node* next = g->adjacent.linked_list[i].head;
            for (int j = 0; j < g->adjacent.linked_list[i].count; ++j)
            {
                printf("%s(%d) ", next->name, next->weight);
                next = next->next;
            }
            printf(";\n");
        }
        break;
    default:
        printf("ERROR!\n");
        return -1;
    }
    putchar('\n');
    return 0;
}

void free_graph(Graph* g)
{
    int lines = g->vertex_count;
    if (g->type == 1) free(g->adjacent.matrix_1d);
    for (int i = 0; i < lines; ++i)
    {
        free(g->vertex_names[i]);
        if (g->type == 1) continue;
        if (g->type == 0)
        {
            free(g->adjacent.matrix_2d[i]);
            continue;
        }
        struct _link_node* next = g->adjacent.linked_list[i].head;
        for (int j = 0; j < g->adjacent.linked_list[i].count; ++j)
        {
            struct _link_node* tmp = next;
            next = next->next;
            free(tmp->name);
            free(tmp);
        }
    }
    if (g->type == 2) free(g->adjacent.linked_list);
    free(g->vertex_names);
    free(g);
}
