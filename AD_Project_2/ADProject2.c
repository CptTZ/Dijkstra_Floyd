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

// Show the shortest path and weight
void show_solution(Result r, char* src, char* end)
{
    if (r.total_weight < 0 || r.route == NULL)
    {
        printf("No path between %s - %s:\n", src, end);
        return;
    }
    printf("Shortest path between %s - %s, using '%s' algorithm:\n", src, end, r.resolver);
    printf("  Distance is: %d.\n  The path is: ", r.total_weight);
    if (r.no_output) return;
    for (int i = 0; r.route[i] != NULL; ++i)
    {
        printf("%s", r.route[i]);
        if (r.route[i + 1] != NULL) printf("->");
    }
    putchar('\n');
}

int main()
{
    printf("INFSCI 2591 Project 2, YIZ141\n\n");
    srand(time(NULL));

    Graph t1, t2, t3;
    Result r1, r2;

    char *start = "v2",
        *end = "v8";

    create_graph_from_file(&t1, "E:\\Source\\C\\AD_Project_2\\AD_Project_2\\t1.txt", 2);
    create_graph_from_file(&t2, "E:\\Source\\C\\AD_Project_2\\AD_Project_2\\t2.txt", 2);
    create_graph_complete_rand(&t3, 10, 2);

    //print_graph(&t1);
    //print_graph(&t2);
    //print_graph(&t3);

    dijkstra(t2, start, end, &r1);
    floyd(t2, start, end, &r2);

    show_solution(r1, start, end);
    show_solution(r2, start, end);

    free_graph(&t1);
    free_graph(&t2);
    free_graph(&t3);
    free_result(&r1);
    free_result(&r2);

    return 0;
}
