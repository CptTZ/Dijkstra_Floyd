/**
 * General Graph related functions
 */

#include "graph.h"

Graph* create_graph_from_file(char* path)
{
    char* content = read_file_content(path);
    Graph* g = malloc(SIZE_GRAPH);



    free(content);
    return g;
}
