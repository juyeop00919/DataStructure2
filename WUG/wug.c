#include <stdio.h>
#include <stdlib.h>
#include "wug.h"

void initGraph(int graph[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void generateConnectedGraph(int graph[V][V], Edge edges[]) {
    int nodes[V];
    for (int i = 0; i < V; i++) nodes[i] = i;

    // 정점 배열 무작위 셔플 (다양한 트리 형태 보장)
    for (int i = V - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }

    int edge_idx = 0;

    // 1. 최소 스패닝 트리 형태로 9개의 간선을 연결하여 연결 그래프 보장
    for (int i = 1; i < V; i++) {
        int u = nodes[rand() % i];
        int v = nodes[i];
        int weight = (rand() % 100) + 1;

        graph[u][v] = weight;
        graph[v][u] = weight;

        edges[edge_idx].u = (u < v) ? u : v;
        edges[edge_idx].v = (u < v) ? v : u;
        edges[edge_idx].weight = weight;
        edge_idx++;
    }

    // 2. 남은 11개의 간선을 중복과 Self-loop 없이 무작위로 추가
    while (edge_idx < E) {
        int u = rand() % V;
        int v = rand() % V;

        if (u != v && graph[u][v] == INF) {
            int weight = (rand() % 100) + 1;

            graph[u][v] = weight;
            graph[v][u] = weight;

            edges[edge_idx].u = (u < v) ? u : v;
            edges[edge_idx].v = (u < v) ? v : u;
            edges[edge_idx].weight = weight;
            edge_idx++;
        }
    }

    // 간선 배열 정렬 (출발점 기준 오름차순 출력용)
    for (int i = 0; i < E - 1; i++) {
        for (int j = i + 1; j < E; j++) {
            if (edges[i].u > edges[j].u || (edges[i].u == edges[j].u && edges[i].v > edges[j].v)) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

void printGraphInfo(Edge edges[]) {
    printf("Graph\n");
    printf("Vertices : %d\n", V);
    printf("Edges    : %d\n\n", E);
    printf("Edges\n");
    for (int i = 0; i < E; i++) {
        printf("(%d, %d) Weight: %d\n", edges[i].u, edges[i].v, edges[i].weight);
    }
    printf("\n");
}

// --- 내부 보조 함수: 다익스트라 최단 거리 정점 찾기 ---
static int getMinDistanceVertex(int dist[], int visited[]) {
    int min = INF;
    int min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// --- 내부 보조 함수: 재귀를 통한 경로 출력 ---
static void printPath(int dest, int prev[]) {
    if (prev[dest] == -1) {
        printf("%d", dest);
        return;
    }
    printPath(prev[dest], prev);
    printf(" -> %d", dest);
}

void findAndPrintAllShortestPaths(int graph[V][V]) {
    printf("Shortest Paths\n\n");

    int pair_count = 0;

    for (int src = 0; src < V - 1; src++) {
        int dist[V];
        int visited[V];
        int prev[V];

        for (int i = 0; i < V; i++) {
            dist[i] = INF;
            visited[i] = 0;
            prev[i] = -1;
        }
        dist[src] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = getMinDistanceVertex(dist, visited);
            visited[u] = 1;

            for (int v = 0; v < V; v++) {
                if (!visited[v] && graph[u][v] != INF && dist[u] != INF
                    && dist[u] + graph[u][v] < dist[v]) {

                    dist[v] = dist[u] + graph[u][v];
                    prev[v] = u;
                }
            }
        }

        // 중복 출력을 막기 위해 src보다 큰 도착점만 출력
        for (int dest = src + 1; dest < V; dest++) {
            printf("%d -> %d\n", src, dest);
            printf("Path     : ");
            printPath(dest, prev);
            printf("\n");
            printf("Distance : %d\n\n", dist[dest]);
            pair_count++;
        }
    }

    printf("Total vertex pairs : %d\n", pair_count);
}