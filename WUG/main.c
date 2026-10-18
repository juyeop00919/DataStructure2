#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "wug.h"

int main() {
    srand((unsigned int)time(NULL));

    int graph[V][V];
    Edge edges[E];

    initGraph(graph);

    generateConnectedGraph(graph, edges);

    printGraphInfo(edges);

    findAndPrintAllShortestPaths(graph);

    return 0;
}