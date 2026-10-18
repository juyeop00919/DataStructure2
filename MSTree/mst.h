#pragma once
#include <stddef.h>
#define V 50
#define SPARSE_E 100
#define DENSE_E 600
#define INF 9999999

// --- 기본 자료구조 정의 ---

// 간선 구조체
typedef struct {
    int u, v, weight;
} Edge;

// 인접 행렬 구조체
typedef struct {
    int matrix[V][V];
} GraphMat;

// 인접 리스트 노드 구조체
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// 인접 리스트 구조체
typedef struct {
    Node* head[V];
} GraphList;

// --- 함수 프로토타입 ---

// 그래프 초기화 및 메모리 해제
void initMat(GraphMat* g);
void initList(GraphList* g);
void freeList(GraphList* g);

// 그래프 구성
void buildMat(GraphMat* g, Edge* edges, int edge_count);
void buildList(GraphList* g, Edge* edges, int edge_count);

// MST 알고리즘
int runKruskal(GraphList* g, int edge_count, int* mst_edges_count);
int runPrim(GraphMat* g, int* mst_edges_count);
