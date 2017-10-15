/**
 * Main method
 * All algorithms are for graphs that are
 * ! connected, undirected and weighted !
 */

#include "common.h"

#include "tools.h"
#include "data_struct.h"
#include "graph.h"


int main()
{
    printf("INFSCI 2591 Project 2, YIZ141\n");
    srand(time(NULL));

    clock_t s = get_current_clock();

    Graph *t1 = create_graph_from_file(".\\t1.txt"),
        *t2 = create_graph_from_file(".\\t2.txt");


    return 0;
}
