#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mst.h"

#define ITERATIONS 10000

// 항상 모든 정점이 연결된 그래프를 생성
void generateConnectedGraph(Edge* edges, int target_edge_count) {
    int nodes[V];
    for (int i = 0; i < V; i++) nodes[i] = i;

    for (int i = V - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }

    int edge_idx = 0;
    int is_edge_added[V][V] = { 0 };

    // 최소 스패닝 트리를 먼저 구성 (연결성 보장)
    for (int i = 1; i < V; i++) {
        int u = nodes[rand() % i];
        int v = nodes[i];
        edges[edge_idx].u = u;
        edges[edge_idx].v = v;
        edges[edge_idx].weight = (rand() % 100) + 1;
        is_edge_added[u][v] = 1;
        is_edge_added[v][u] = 1;
        edge_idx++;
    }

    // 남은 간선 무작위 채우기
    while (edge_idx < target_edge_count) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v && !is_edge_added[u][v]) {
            edges[edge_idx].u = u;
            edges[edge_idx].v = v;
            edges[edge_idx].weight = (rand() % 100) + 1;
            is_edge_added[u][v] = 1;
            is_edge_added[v][u] = 1;
            edge_idx++;
        }
    }
}

int main() {
    srand((unsigned int)time(NULL));

    Edge sparse_edges[SPARSE_E];
    Edge dense_edges[DENSE_E];

    generateConnectedGraph(sparse_edges, SPARSE_E);
    generateConnectedGraph(dense_edges, DENSE_E);

    clock_t start, end;
    double exec_time;
    int mst_edges, mst_cost;

    // Case 1 : Sparse Graph - Adjacency List - Kruskal
    GraphList gListSparse; initList(&gListSparse);
    buildList(&gListSparse, sparse_edges, SPARSE_E);

    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        mst_cost = runKruskal(&gListSparse, SPARSE_E, &mst_edges);
    }
    end = clock();
    // 10,000번의 총합을 10,000으로 나누어 1회 평균 마이크로초(us) 산출
    exec_time = (((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0) / ITERATIONS;

    size_t mem_kruskal_sparse = sizeof(GraphList) + (SPARSE_E * 2 * sizeof(Node))
        + (SPARSE_E * sizeof(Edge)) + (2 * V * sizeof(int));

    printf("Case 1 : Sparse Graph - Adjacency List - Kruskal\n");
    printf("Vertices      : %d\n", V);
    printf("Edges         : %d\n", SPARSE_E);
    printf("MST Edges     : %d\n", mst_edges);
    printf("MST Cost      : %d\n", mst_cost);
    printf("Memory        : %zu Bytes\n", mem_kruskal_sparse);
    printf("Execution Time: %.2f us (Avg of %d runs)\n\n", exec_time, ITERATIONS);
    freeList(&gListSparse);

    // Case 2 : Dense Graph - Adjacency List - Kruskal
    GraphList gListDense; initList(&gListDense);
    buildList(&gListDense, dense_edges, DENSE_E);

    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        mst_cost = runKruskal(&gListDense, DENSE_E, &mst_edges);
    }
    end = clock();
    exec_time = (((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0) / ITERATIONS;

    size_t mem_kruskal_dense = sizeof(GraphList) + (DENSE_E * 2 * sizeof(Node))
        + (DENSE_E * sizeof(Edge)) + (2 * V * sizeof(int));

    printf("Case 2 : Dense Graph - Adjacency List - Kruskal\n");
    printf("Vertices      : %d\n", V);
    printf("Edges         : %d\n", DENSE_E);
    printf("MST Edges     : %d\n", mst_edges);
    printf("MST Cost      : %d\n", mst_cost);
    printf("Memory        : %zu Bytes\n", mem_kruskal_dense);
    printf("Execution Time: %.2f us (Avg of %d runs)\n\n", exec_time, ITERATIONS);
    freeList(&gListDense);

    // Case 3 : Sparse Graph - Adjacency Matrix - Prim
    GraphMat gMatSparse; initMat(&gMatSparse);
    buildMat(&gMatSparse, sparse_edges, SPARSE_E);

    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        mst_cost = runPrim(&gMatSparse, &mst_edges);
    }
    end = clock();
    exec_time = (((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0) / ITERATIONS;

    size_t mem_prim_sparse = sizeof(GraphMat) + (3 * V * sizeof(int));

    printf("Case 3 : Sparse Graph - Adjacency Matrix - Prim\n");
    printf("Vertices      : %d\n", V);
    printf("Edges         : %d\n", SPARSE_E);
    printf("MST Edges     : %d\n", mst_edges);
    printf("MST Cost      : %d\n", mst_cost);
    printf("Memory        : %zu Bytes\n", mem_prim_sparse);
    printf("Execution Time: %.2f us (Avg of %d runs)\n\n", exec_time, ITERATIONS);

    // Case 4 : Dense Graph - Adjacency Matrix - Prim
    GraphMat gMatDense; initMat(&gMatDense);
    buildMat(&gMatDense, dense_edges, DENSE_E);

    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        mst_cost = runPrim(&gMatDense, &mst_edges);
    }
    end = clock();
    exec_time = (((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0) / ITERATIONS;

    size_t mem_prim_dense = mem_prim_sparse;

    printf("Case 4 : Dense Graph - Adjacency Matrix - Prim\n");
    printf("Vertices      : %d\n", V);
    printf("Edges         : %d\n", DENSE_E);
    printf("MST Edges     : %d\n", mst_edges);
    printf("MST Cost      : %d\n", mst_cost);
    printf("Memory        : %zu Bytes\n", mem_prim_dense);
    printf("Execution Time: %.2f us (Avg of %d runs)\n", exec_time, ITERATIONS);

    return 0;
}