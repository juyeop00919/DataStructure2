#include <stdio.h>
#include <stdlib.h>
#include "mst.h"

// --- 그래프 초기화 함수 ---

void initMat(GraphMat* g) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

void initList(GraphList* g) {
    for (int i = 0; i < V; i++) {
        g->head[i] = NULL;
    }
}

void freeList(GraphList* g) {
    for (int i = 0; i < V; i++) {
        Node* curr = g->head[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        g->head[i] = NULL;
    }
}

void buildMat(GraphMat* g, Edge* edges, int edge_count) {
    for (int i = 0; i < edge_count; i++) {
        g->matrix[edges[i].u][edges[i].v] = edges[i].weight;
        g->matrix[edges[i].v][edges[i].u] = edges[i].weight;
    }
}

void buildList(GraphList* g, Edge* edges, int edge_count) {
    for (int i = 0; i < edge_count; i++) {
        Node* n1 = (Node*)malloc(sizeof(Node));
        n1->vertex = edges[i].v;
        n1->weight = edges[i].weight;
        n1->next = g->head[edges[i].u];
        g->head[edges[i].u] = n1;

        Node* n2 = (Node*)malloc(sizeof(Node));
        n2->vertex = edges[i].u;
        n2->weight = edges[i].weight;
        n2->next = g->head[edges[i].v];
        g->head[edges[i].v] = n2;
    }
}

// --- Kruskal 알고리즘 보조 함수 (Union-Find) ---

int findParent(int parent[], int i) {
    if (parent[i] == i) return i;
    return parent[i] = findParent(parent, parent[i]); // 경로 압축
}

void unionSet(int parent[], int rank[], int x, int y) {
    int xroot = findParent(parent, x);
    int yroot = findParent(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    }
    else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    }
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// --- Kruskal 알고리즘 구현 ---
int runKruskal(GraphList* g, int edge_count, int* mst_edges_count) {
    Edge* edge_array = (Edge*)malloc(edge_count * sizeof(Edge));
    int k = 0;

    // 인접 리스트에서 중복을 피해 간선 추출 (u < v 인 경우만)
    for (int i = 0; i < V; i++) {
        Node* curr = g->head[i];
        while (curr != NULL) {
            if (i < curr->vertex) {
                edge_array[k].u = i;
                edge_array[k].v = curr->vertex;
                edge_array[k].weight = curr->weight;
                k++;
            }
            curr = curr->next;
        }
    }

    qsort(edge_array, edge_count, sizeof(Edge), compareEdges);

    int parent[V];
    int rank[V];
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int mst_weight = 0;
    int edges_added = 0;

    for (int i = 0; i < edge_count && edges_added < V - 1; i++) {
        int u = edge_array[i].u;
        int v = edge_array[i].v;

        int x = findParent(parent, u);
        int y = findParent(parent, v);

        if (x != y) {
            mst_weight += edge_array[i].weight;
            edges_added++;
            unionSet(parent, rank, x, y);
        }
    }

    *mst_edges_count = edges_added;
    free(edge_array);
    return mst_weight;
}


// --- Prim 알고리즘 보조 함수 ---
int minKey(int key[], int mstSet[]) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// --- Prim 알고리즘 구현 ---
int runPrim(GraphMat* g, int* mst_edges_count) {
    int parent[V];
    int key[V];
    int mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (g->matrix[u][v] && mstSet[v] == 0 && g->matrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = g->matrix[u][v];
            }
        }
    }

    int mst_weight = 0;
    int edges_added = 0;
    for (int i = 1; i < V; i++) {
        mst_weight += g->matrix[i][parent[i]];
        edges_added++;
    }

    *mst_edges_count = edges_added;
    return mst_weight;
}