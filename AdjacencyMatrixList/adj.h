#pragma once

#define V 100
#define SPARSE_E 100
#define DENSE_E 4000

typedef struct {
    int u, v;
} Edge;

// 인접 행렬 
typedef struct {
    int matrix[V][V];
} GraphMat;

// 인접 리스트 노드 
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 인접 리스트 
typedef struct {
    Node* head[V];
} GraphList;

// 행렬
void initMat(GraphMat* g);
int insertEdgeMat(GraphMat* g, int u, int v);
int deleteEdgeMat(GraphMat* g, int u, int v);
int checkConnMat(GraphMat* g, int u, int v);
int getAdjMat(GraphMat* g, int u);

// 리스트
void initList(GraphList* g);
int insertEdgeList(GraphList* g, int u, int v);
int deleteEdgeList(GraphList* g, int u, int v);
int checkConnList(GraphList* g, int u, int v);
int getAdjList(GraphList* g, int u);
void freeList(GraphList* g);


