#pragma once
#define V 10
#define E 20
#define INF 9999999

// 간선 정보를 저장하는 구조체
typedef struct {
    int u, v, weight;
} Edge;

// 그래프 초기화
void initGraph(int graph[V][V]);

// 연결 그래프 생성 (정점 10개, 간선 20개)
void generateConnectedGraph(int graph[V][V], Edge edges[]);

// 생성된 그래프의 간선 정보 출력
void printGraphInfo(Edge edges[]);

// 모든 정점 쌍(45개)의 최단경로 탐색 및 출력
void findAndPrintAllShortestPaths(int graph[V][V]);
