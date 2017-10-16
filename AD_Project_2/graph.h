/**
 * General Graph related functions
 */

#pragma once

#include "common.h"
#include "tools.h"

#include "data_struct.h"


/**
 * \brief Generate a complete undirected graph with random weight
 * \param g Empty graph
 * \param size Graph size
 * \param type Graph type
 * \return running time
 */
double create_graph_complete_rand(Graph* g, int size, char type);

/**
 * \brief Generate graph from test cases file
 * \param g Graph
 * \param path Path to text file
 * \param type Graph type
 * \return Creation time
 */
double create_graph_from_file(Graph *g, char* path, char type);

/**
* \brief Find direct vertex distance by vertex name
* \param g Graph
* \param source Source vertex
* \param target Target vertex
* \return weight (-1: No route, -2: Wrong graph)
*/
int get_node_weight_in_graph_list(Graph g, char* source, char* target);

/**
* \brief Find vertex index by name
* \param g Graph
* \param name Vertex name
* \return index (-1 for no)
*/
int find_index_by_vertex_name(Graph* g, char* name);

/**
* \brief Find vertex name by index
* \param g Graph
* \param i Vertex index
* \return Name
*/
char* find_vertex_name_by_index(Graph* g, int i);

/**
 * \brief Print out a graph (Debug)
 * \param g Graph
 * \return Result
 */
int print_graph(Graph *g);


/**
 * \brief Freeup RAM (Without g itself)
 * \param g Graph
 */
void free_graph(Graph* g);
