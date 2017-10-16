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

// Output data for exection time analysis (plot)
void output_csv(char* path, int total_tests, char* type, int* size, double* exec_time)
{
    FILE* fp = fopen(path, "w");
    if (fp == NULL)
    {
        puts("Open file failed!");
        return;
    }
    fprintf(fp, "Structure Type,Vertex Count,Exec Time\n");

    for (int i = 0; i < total_tests; ++i)
    {
        char* a;
        if (type[i] == 0) a = "Matrix 2D";
        else if (type[i] == 1) a = "Matrix 1D";
        else if (type[i] == 2) a = "Linked List";
        else continue;
        fprintf(fp, "%s,%d,%lf\n", a, size[i], exec_time[i]);
    }

    fclose(fp);
}

int main()
{
    printf("INFSCI 2591 Project 2, YIZ141\n");
    srand(time(NULL));

    Graph t1, t2, t3;
    Result r1, r2, r3;

    create_graph_from_file(&t1, "E:\\Source\\C\\AD_Project_2\\AD_Project_2\\t1.txt", 0);
    create_graph_from_file(&t2, "E:\\Source\\C\\AD_Project_2\\AD_Project_2\\t2.txt", 0);
    create_graph_complete_rand(&t3, 10, 2);

    dijkstra(t1, "v1", "v8", &r1);
    floyd(t1, "v2", "v8", &r2);

    print_graph(&t1);
    print_graph(&t2);
    print_graph(&t3);

    free_graph(&t1);
    free_graph(&t2);
    free_graph(&t3);

    return 0;
}
