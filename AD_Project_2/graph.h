/**
 * General Graph related functions
 */

#pragma once

#include "common.h"
#include "tools.h"

#include "data_struct.h"


/**
 * \brief Generate graph from test cases file
 * \param path Path to text file
 * \return New Graph
 */
Graph* create_graph_from_file(char* path);


/**
 * \brief Print out a graph (Debug)
 * \param g Graph
 * \return Result
 */
int print_graph(Graph *g);


/**
 * \brief Freeup RAM
 * \param g Graph
 */
void free_graph(Graph* g);
