/**
 * Floyd-Warshall Algorithm
 */

#pragma once

#include "data_struct.h"
#include "graph.h"
#include "tools.h"

/**
 * \brief Floyd-Warshall for undirected and connected graph
 * \param g Graph
 * \param source Name for start vertex
 * \param target Name for end vertex
 * \param result Path result for printing
 * \return Running time
 */
double floyd(Graph g, char* source, char* target, Result* result);
