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

    Graph *t1 = create_graph_from_file(".\\t1.txt", 1),
        *t2 = create_graph_from_file(".\\t2.txt", 1),
        t3;

    create_graph_complete_rand(&t3, 5, 1);
    print_graph(t1);
    print_graph(t2);
    print_graph(&t3);

    return 0;
}
