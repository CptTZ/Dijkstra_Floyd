/**
 * General Graph related functions
 */

#pragma once

#include "common.h"
#include "tools.h"

#include "data_struct.h"


/**
 * \brief Generate graph from a text file (like test cases)
 * \param path Path to text file
 * \return New Graph
 */
Graph* create_graph_from_file(char* path);
