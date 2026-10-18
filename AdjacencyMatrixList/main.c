#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "adj.h"


void runPerformanceTest(Edge* edges, int edge_count, const char* graph_type, int case_num) {
    GraphMat mat; initMat(&mat);
    GraphList list; initList(&list);

    //선택된 간선들로 그래프 구성
    for (int i = 0; i < edge_count; i++) {
        mat.matrix[edges[i].u][edges[i].v] = 1;
        mat.matrix[edges[i].v][edges[i].u] = 1;

        Node* n1 = (Node*)malloc(sizeof(Node));
        n1->vertex = edges[i].v; n1->next = list.head[edges[i].u]; list.head[edges[i].u] = n1;

        Node* n2 = (Node*)malloc(sizeof(Node));
        n2->vertex = edges[i].u; n2->next = list.head[edges[i].v]; list.head[edges[i].v] = n2;
    }

    //테스트 정점/간선 선정
    int ins_u, ins_v;
    while (1) {
        ins_u = rand() % V; ins_v = rand() % V;
        if (ins_u != ins_v && mat.matrix[ins_u][ins_v] == 0) break; // 존재하지 않는 간선 선택
    }

    int del_idx = rand() % edge_count; // 존재하는 간선 무작위 선택
    int del_u = edges[del_idx].u;
    int del_v = edges[del_idx].v;

    int chk_u, chk_v; // 임의의 두 정점
    do { chk_u = rand() % V; chk_v = rand() % V; } while (chk_u == chk_v);

    int adj_u = rand() % V; // 임의의 기준 정점

    // 인접 행렬 성능 측정
    size_t mat_mem = sizeof(GraphMat);
    int mat_ins_comp = insertEdgeMat(&mat, ins_u, ins_v);
    int mat_del_comp = deleteEdgeMat(&mat, del_u, del_v);
    int mat_conn_comp = checkConnMat(&mat, chk_u, chk_v);
    int mat_adj_comp = getAdjMat(&mat, adj_u);

    printf("Case %d : %s Graph - Adjacency Matrix\n", case_num, graph_type);
    printf("Memory                         : %zu Bytes\n", mat_mem);
    printf("Edge insertion comparisons     : %d\n", mat_ins_comp);
    printf("Edge deletion comparisons      : %d\n", mat_del_comp);
    printf("Connectivity check comparisons : %d\n", mat_conn_comp);
    printf("Adjacent vertices comparisons  : %d\n\n", mat_adj_comp);

    // 인접 리스트 성능 측정
    size_t list_mem = sizeof(GraphList) + (edge_count * 2 * sizeof(Node));
    int list_ins_comp = insertEdgeList(&list, ins_u, ins_v);
    int list_del_comp = deleteEdgeList(&list, del_u, del_v);
    int list_conn_comp = checkConnList(&list, chk_u, chk_v);
    int list_adj_comp = getAdjList(&list, adj_u);

    printf("Case %d : %s Graph - Adjacency List\n", case_num + 1, graph_type);
    printf("Memory                         : %zu Bytes\n", list_mem);
    printf("Edge insertion comparisons     : %d\n", list_ins_comp);
    printf("Edge deletion comparisons      : %d\n", list_del_comp);
    printf("Connectivity check comparisons : %d\n", list_conn_comp);
    printf("Adjacent vertices comparisons  : %d\n\n", list_adj_comp);

    freeList(&list);
}


int main() {
    srand((unsigned int)time(NULL));

    // 100개 정점의 모든 가능한 무방향 간선 생성 (100 * 99 / 2 = 4950개)
    Edge all_edges[4950];
    int edge_idx = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            all_edges[edge_idx].u = i;
            all_edges[edge_idx].v = j;
            edge_idx++;
        }
    }

    // Fisher-Yates 셔플로 간선을 무작위로 섞음 (편향 방지)
    for (int i = 4949; i > 0; i--) {
        int j = rand() % (i + 1);
        Edge temp = all_edges[i];
        all_edges[i] = all_edges[j];
        all_edges[j] = temp;
    }

    // 성능 비교
    runPerformanceTest(all_edges, SPARSE_E, "Sparse", 1); // Case 1 & 2
    runPerformanceTest(all_edges, DENSE_E, "Dense", 3);   // Case 3 & 4

    return 0;
}