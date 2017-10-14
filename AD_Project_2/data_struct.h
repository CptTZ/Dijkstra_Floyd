/**
 * Define data structures for this project
 */

#pragma once

#define LINK_NODE_SIZE sizeof(struct _link_node)
#define EDGE_LINKED_SIZE sizeof(struct _edge_linked_list)
#define GRAPH_SIZE sizeof(struct _graph)
#define POINTER_SIZE sizeof(int*)

struct _link_node
{
    int weight;
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
    union
    {
        // 2D adjacent matrix
        int** AdjacentMatrix2D;
        // Linked List
        struct _edge_linked_list* AdjacentLinkedList;
        // 1D lower triangle adjacent matrix
        int* AdjacentMatrix1D;
    } data;
} Graph;
