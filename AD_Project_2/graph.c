/**
 * General Graph related functions
 */

#include "graph.h"

/**
 * \brief Prefix = 'v', names like v1, v2, ..., v10, ..., vn
 * \param prefix 'v'
 * \param size vertex size
 * \return names names array
 */
char** gen_vertex_name(char prefix, int size);

/**
 * \brief Add a new node to the graph
 * \param g Graph
 * \param weight New node weight
 * \param name New node name (Shallow copy)
 */
void add_new_node_to_graph_list(struct _edge_linked_list* g, int weight, char* name);

/**
 * \brief Malloc for 2d matrix
 * \param size size
 * \return 2d matrix
 */
int** malloc_matrix_2d(int size);

/**
* \brief Malloc for 1d matrix
* \param size size
* \return 1d matrix
*/
int* malloc_matrix_1d(int size);

/**
 * \brief Free graph adj
 * \param g Graph
 */
void free_graph_adj(Graph* g);

//TODO: Generate sprase graph

double create_graph_complete_rand(Graph* g, int size, char type)
{
    g->vertex_count = size;
    g->edge_count = size * (size - 1) / 2; // Formula for complete graph
    g->vertex_names = gen_vertex_name('v', size);
    g->type = type;
    int tmp;
    struct _edge_linked_list* list;

    // Start constructing data structure
    switch (type)
    {
    case 0:
        g->adjacent.matrix_2d = malloc_matrix_2d(size);
        for (int i = 0; i < size; ++i)
        {
            for (int j = i; j < size; ++j)
            {
                g->adjacent.matrix_2d[i][j] = (i == j ? 0 : next_rnd_int(RND_UPPER));
            }
            // Transpose
            for (int j = 0; j < size; ++j)
            {
                g->adjacent.matrix_2d[j][i] = g->adjacent.matrix_2d[i][j];
            }
        }
        break;

    case 1:
        g->adjacent.matrix_1d = malloc_matrix_1d(g->edge_count + size);
        tmp = 0;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                g->adjacent.matrix_1d[tmp++] = (i == j ? 0 : next_rnd_int(RND_UPPER));
            }
        }
        break;

    case 2:
        list = malloc(size * SIZE_EDGE_LINKED);
        for (int i = 0; i < size; ++i)
        {
            list[i].count = 0;
            list[i].head = NULL;
            for (int k = 0; k < size; ++k)
            {
                if (i == k) continue; // Linked list doesn't take self into consideration
                add_new_node_to_graph_list(list + i, next_rnd_int(RND_UPPER),
                    find_vertex_name_by_index(*g, k));
            }
        }
        g->adjacent.linked_list = list;
        break;

    default:
        return -1;
    }


    return 0;
}

double create_graph_from_file(Graph* g, char* path, char type)
{
    char* file_data = read_file_content(path);

    clock_t start = get_current_clock();
    g->type = 0;

    int lines = 1;
    // count lines in order to make array
    for (int i = 0; file_data[i] != '\0'; ++i)
    {
        if (file_data[i] == '\n') lines++;
    }
    g->vertex_count = lines;

    // Malloc 2D array and vertex names
    g->adjacent.matrix_2d = malloc_matrix_2d(lines);
    g->vertex_names = gen_vertex_name('v', lines);

    // Read weight and build the graph
    int current_line = 0, current_col = 0, j, weight, edges = 0, tmp_col;
    for (int i = 0; file_data[i] != '\0'; ++i)
    {
        switch (file_data[i])
        {
        case '\r':
        case ' ':
            break;
        case '\n':
            current_line++;
            current_col = 0;
            break;
        case '.':
            tmp_col = current_col;
            g->adjacent.matrix_2d[current_line][current_col++] = (current_line == tmp_col ? 0 : INT_AS_INFI);
            break;
        default:
            // It's weight now
            for (j = i, weight = 0; file_data[j] >= '0' && file_data[j] <= '9'; ++j)
            {
                weight = weight * 10 + file_data[j] - '0';
            }
            g->adjacent.matrix_2d[current_line][current_col++] = weight;
            i = j - 1;
            edges++;
            break;
        }
    }
    g->edge_count = edges / 2; // Undirected

    // If type is not 2D matrix, then convert it
    if (type == 1)
    {
        int tmp = 0, *tmp_data = malloc_matrix_1d((1 + lines) * lines / 2);
        for (int i = 0; i < lines; ++i)
        {
            for (int k = 0; k <= i; ++k)
            {
                tmp_data[tmp++] = g->adjacent.matrix_2d[i][k];
            }
        }
        free_graph_adj(g);
        g->adjacent.matrix_1d = tmp_data;
    }
    else if (type == 2)
    {
        struct _edge_linked_list* list = malloc(lines * SIZE_EDGE_LINKED);
        for (int i = 0; i < lines; ++i)
        {
            list[i].count = 0;
            list[i].head = NULL;
            for (int k = 0; k < lines; ++k)
            {
                int w1 = g->adjacent.matrix_2d[i][k];
                if (w1 == INT_AS_INFI || w1 == 0) continue;
                add_new_node_to_graph_list(list + i, w1, find_vertex_name_by_index(*g, k));
            }
        }
        free_graph_adj(g);
        g->adjacent.linked_list = list;
    }

    g->type = type;
    clock_t end = get_current_clock();

    free(file_data);
    return clock_to_ms(end, start);
}

int get_node_weight_in_graph_list(Graph g, char* source, char* target)
{
    if (g.type != 2) return -2;
    int idx_source = find_index_by_vertex_name(g, source);

    struct _edge_linked_list src = g.adjacent.linked_list[idx_source];
    struct _link_node* next = src.head;
    for (unsigned int i = 0; i < src.count; ++i)
    {
        if (strcmp(next->name, target) == 0) return i;
        next = next->next;
    }

    return -1;
}

void add_new_node_to_graph_list(struct _edge_linked_list* g, int weight, char* name)
{
    struct _link_node* new_node = malloc(SIZE_LINK_NODE);
    new_node->weight = weight;
    new_node->name = name;
    new_node->next = g->head;

    g->head = new_node;
    g->count++;
}

int** malloc_matrix_2d(int size)
{
    int** res = (int**)malloc(size * SIZE_POINTER_1);
    for (int i = 0; i < size; ++i)
    {
        res[i] = malloc_matrix_1d(size);
    }
    return res;
}

int* malloc_matrix_1d(int size)
{
    return (int*)malloc(size * SIZE_INT);
}

char** gen_vertex_name(char prefix, int size)
{
    char** names = (char**)malloc(size * SIZE_POINTER_1);
    for (int i = 0; i < size; ++i)
    {
        int tmp = i + 1;
        int len = (int)log10(tmp) + 1;
        char* tmp_name = malloc((2 + len) * SIZE_CHAR);
        tmp_name[0] = prefix;
        for (int j = 0; tmp > 0; ++j)
        {
            tmp_name[len - j] = tmp % 10 + '0';
            tmp /= 10;
        }
        tmp_name[len + 1] = '\0';
        names[i] = tmp_name;
    }
    return names;
}

char* find_vertex_name_by_index(Graph g, int i)
{
    int len = g.vertex_count;
    if (i > len - 1) return NULL;
    return g.vertex_names[i];
}

int find_index_by_vertex_name(Graph g, char* name)
{
    int len = g.vertex_count;
    for (int i = 0; i < len; ++i)
    {
        if (strcmp(name, g.vertex_names[i]) == 0)
            return i;
    }
    return -1;
}

int print_graph(Graph* g)
{
    int ll = g->vertex_count, tmp;
    printf("Graph have %d vertices, %d edges, internal structure as follows: \n", ll, g->edge_count);
    switch (g->type)
    {
    case 0:
        for (int i = 0; i < ll; ++i)
        {
            for (int j = 0; j < ll; ++j)
            {
                int w = g->adjacent.matrix_2d[i][j];
                if (w == INT_AS_INFI)
                    printf(" . ");
                else
                    printf("%3d", w);
            }
            putchar('\n');
        }
        break;
    case 1:
        tmp = 0;
        for (int i = 0; i < ll; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                int w = g->adjacent.matrix_1d[tmp++];
                if (w == INT_AS_INFI)
                    printf(" . ");
                else
                    printf("%3d", w);
            }
            putchar('\n');
        }
        break;
    case 2:
        for (int i = 0; i < ll; ++i)
        {
            printf("%s: ", g->vertex_names[i]);
            struct _link_node* next = g->adjacent.linked_list[i].head;
            for (unsigned int j = 0; j < g->adjacent.linked_list[i].count; ++j)
            {
                printf("%s(%d) ", next->name, next->weight);
                next = next->next;
            }
            printf("\n");
        }
        break;
    default:
        printf("ERROR!\n");
        return -1;
    }
    putchar('\n');
    return 0;
}

void free_graph_adj(Graph* g)
{
    int lines = g->vertex_count;
    if (g->type == 1)
    {
        free(g->adjacent.matrix_1d);
        return;
    }
    for (int i = 1; i < lines; ++i)
    {
        if (g->type == 0)
        {
            free(g->adjacent.matrix_2d[i]);
            continue;
        }
        struct _link_node* next = g->adjacent.linked_list[i].head;
        for (unsigned int j = 0; j < g->adjacent.linked_list[i].count; ++j)
        {
            struct _link_node* tmp = next;
            next = next->next;
            free(tmp);
        }
    }
}

void free_graph(Graph* g)
{
    for (unsigned int i = 0; i < g->vertex_count; ++i)
    {
        free(g->vertex_names[i]);
    }
    free_graph_adj(g);
    if (g->type == 2) free(g->adjacent.linked_list);
    free(g->vertex_names);
}
