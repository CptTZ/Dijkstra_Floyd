/**
 * Main method
 * All algorithms are for graphs that are
 * ! connected, undirected and weighted !
 */

#include "common.h"

#include "data_struct.h"
#include "graph.h"
#include "dijkstra.h"
#include "floyd.h"


int main()
{
    printf("INFSCI 2591 Project 2, YIZ141\n");
    srand(time(NULL));

    Graph t1, t2, t3;
    Result *r1, *r2, *r3;

    create_graph_from_file(&t1, "E:\\Source\\C\\AD_Project_2\\AD_Project_2\\t1.txt", 0);
    create_graph_from_file(&t2, "E:\\Source\\C\\AD_Project_2\\AD_Project_2\\t2.txt", 1);
    create_graph_complete_rand(&t3, 10, 0);

    dijkstra(t1, "v1", "v8", r1);
    floyd(t1, "v2", "v8", r2);

    print_graph(&t1);
    print_graph(&t2);
    print_graph(&t3);

    free_graph(&t1);
    free_graph(&t2);
    free_graph(&t3);

    return 0;
}
