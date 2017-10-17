/**
 * Define data structures for this project
 */

#pragma once

#define SIZE_LINK_NODE sizeof(struct _link_node)
#define SIZE_EDGE_LINKED sizeof(struct _edge_linked_list)
#define SIZE_GRAPH sizeof(struct _graph)
#define SIZE_RESULT sizeof(struct _f_result)

#define SIZE_POINTER_1 sizeof(int*)
#define SIZE_INT sizeof(int)
#define SIZE_CHAR sizeof(char)

#define BOOL char
#define TRUE 1
#define FALSE 0

struct _link_node
{
    int weight;
    int id;
    char* name;
    struct _link_node* next;
};

struct _edge_linked_list
{
    unsigned int count;
    struct _link_node* head;
};

// Wrap everything in one struct
typedef struct _graph
{
    unsigned int edge_count,
                 vertex_count; // May have empty value for that
    char type; // 0=2D, 1=1D, 2=List
    char** vertex_names; // Vertex names
    union
    {
        // 2D adjacent matrix
        int** matrix_2d;
        // Linked List
        struct _edge_linked_list* linked_list;
        // 1D lower triangle adjacent matrix
        int* matrix_1d;
    } adjacent;
} Graph;

// Final printable result
typedef struct _f_result
{
    BOOL no_output;
    char* resolver;
    int total_weight;
    char** route;
} Result;
