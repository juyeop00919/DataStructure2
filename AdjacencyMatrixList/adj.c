#include <stdlib.h>
#include "adj.h"

//인접 행렬

void initMat(GraphMat* g) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

int insertEdgeMat(GraphMat* g, int u, int v) {
    g->matrix[u][v] = 1;
    g->matrix[v][u] = 1;
	return 1; // 비교 1회
}

int deleteEdgeMat(GraphMat* g, int u, int v) {
    g->matrix[u][v] = 0;
    g->matrix[v][u] = 0;
    return 1; // 비교 1회
}

int checkConnMat(GraphMat* g, int u, int v) {
    return 1; //접근 1회
}

int getAdjMat(GraphMat* g, int u) {
    int comps = 0;
    for (int i = 0; i < V; i++) {
        comps++; // 각 정점마다 연결 여부 확인
        int temp = g->matrix[u][i];
    }
    return comps; // 항상 100회
}


//인접 리스트

void initList(GraphList* g) {
    for (int i = 0; i < V; i++) {
        g->head[i] = NULL;
    }
}

int insertEdgeList(GraphList* g, int u, int v) {
    int comps = 0;

    // u의 리스트에서 v 존재 여부 확인
    Node* curr = g->head[u];
    while (curr != NULL) {
        comps++;
        if (curr->vertex == v) break;
        curr = curr->next;
    }
    // v의 리스트에서 u 존재 여부 확인
    curr = g->head[v];
    while (curr != NULL) {
        comps++;
        if (curr->vertex == u) break;
        curr = curr->next;
    }

    // 맨 앞에 노드 삽입
    Node* newNodeU = (Node*)malloc(sizeof(Node));
    newNodeU->vertex = v;
    newNodeU->next = g->head[u];
    g->head[u] = newNodeU;

    Node* newNodeV = (Node*)malloc(sizeof(Node));
    newNodeV->vertex = u;
    newNodeV->next = g->head[v];
    g->head[v] = newNodeV;

    return comps;
}

int deleteEdgeList(GraphList* g, int u, int v) {
    int comps = 0;

    // u의 리스트에서 v 찾아 삭제
    Node* curr = g->head[u];
    Node* prev = NULL;
    while (curr != NULL) {
        comps++;
        if (curr->vertex == v) {
            if (prev == NULL) g->head[u] = curr->next;
            else prev->next = curr->next;
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    // v의 리스트에서 u 찾아 삭제
    curr = g->head[v];
    prev = NULL;
    while (curr != NULL) {
        comps++;
        if (curr->vertex == u) {
            if (prev == NULL) g->head[v] = curr->next;
            else prev->next = curr->next;
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    return comps;
}

int checkConnList(GraphList* g, int u, int v) {
    int comps = 0;
    Node* curr = g->head[u];
    while (curr != NULL) {
        comps++;
        if (curr->vertex == v) return comps; 
        curr = curr->next;
    }
    return comps; 
}

int getAdjList(GraphList* g, int u) {
    int comps = 0;
    Node* curr = g->head[u];
    while (curr != NULL) {
        comps++; 
        curr = curr->next;
    }
    return comps;
}

void freeList(GraphList* g) {
    for (int i = 0; i < V; i++) {
        Node* curr = g->head[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
}