#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVLTree.h"

#define DATA_SIZE 100
#define SEARCH_SIZE 50
#define MAX_VAL 1000

// 배열 순차 탐색 함수
bool sequentialSearch(int arr[], int size, int key, int* compCount) {
    *compCount = 0;
    for (int i = 0; i < size; i++) {
        (*compCount)++;
        if (arr[i] == key) {
            return true;
        }
    }
    return false;
}

int main() {
    srand((unsigned int)time(NULL));

    int generated[DATA_SIZE];
    int arr[DATA_SIZE];
    int uniqueCount = 0;
    int duplicateCount = 0;

    TreeNode* bstRoot = NULL;
    TreeNode* avlRoot = NULL;

    int arrComps = 0;
    int bstComps = 0;
    int avlComps = 0;

    // [1] 데이터 생성 및 저장
    printf("=== [1] Generated 100 Numbers ===\n");
    for (int i = 0; i < DATA_SIZE; i++) {
        int val = rand() % (MAX_VAL + 1);
        generated[i] = val;

        // 1. Array 삽입 및 비교 횟수 측정
        bool foundInArr = false;
        for (int j = 0; j < uniqueCount; j++) {
            arrComps++;
            if (arr[j] == val) {
                foundInArr = true;
                break;
            }
        }
        if (!foundInArr) {
            arr[uniqueCount++] = val;
        }
        else {
            duplicateCount++;
        }

        // 2. BST 삽입 및 비교 횟수 측정
        bool insertedBST = false;
        bstRoot = insertBST(bstRoot, val, &bstComps, &insertedBST);

        // 3. AVL 삽입 및 비교 횟수 측정
        bool insertedAVL = false;
        avlRoot = insertAVL(avlRoot, val, &avlComps, &insertedAVL);

        // 출력 형식
        printf("%4d ", val);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");

    // [2] 통계 및 구조 크기/높이 출력
    printf("Stored values : %d\n", uniqueCount);
    printf("Duplicates ignored : %d\n\n", duplicateCount);

    printf("Construction\n");
    printf("Array comparisons : %d\n", arrComps);
    printf("BST comparisons   : %d\n", bstComps);
    printf("AVL comparisons   : %d\n\n", avlComps);

    printf("Structure\n");
    printf("Array length : %d\n", uniqueCount);
    printf("BST height   : %d\n", getTreeHeight(bstRoot));
    printf("AVL height   : %d\n\n", getTreeHeight(avlRoot));

    // [3] 탐색 데이터 생성
    int searchKeys[SEARCH_SIZE];
    printf("=== [2] Generated 50 Search Keys ===\n");
    for (int i = 0; i < SEARCH_SIZE; i++) {
        searchKeys[i] = rand() % (MAX_VAL + 1);
        printf("%4d ", searchKeys[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");

    // [4] 탐색 수행 및 결과 출력
    int seqTotalComps = 0, bstTotalComps = 0, avlTotalComps = 0;

    printf("=== [3] Search Results ===\n");
    for (int i = 0; i < SEARCH_SIZE; i++) {
        int target = searchKeys[i];
        int seqC = 0, bstC = 0, avlC = 0;

        bool seqRes = sequentialSearch(arr, uniqueCount, target, &seqC);
        bool bstRes = searchBST(bstRoot, target, &bstC);
        bool avlRes = searchAVL(avlRoot, target, &avlC);

        seqTotalComps += seqC;
        bstTotalComps += bstC;
        avlTotalComps += avlC;

        printf("Search Key : %d\n\n", target);

        printf("Sequential Search\n");
        printf("Result      : %s\n", seqRes ? "Found" : "Not Found");
        printf("Comparisons : %d\n\n", seqC);

        printf("BST Search\n");
        printf("Result      : %s\n", bstRes ? "Found" : "Not Found");
        printf("Comparisons : %d\n\n", bstC);

        printf("AVL Search\n");
        printf("Result      : %s\n", avlRes ? "Found" : "Not Found");
        printf("Comparisons : %d\n", avlC);
        printf("--------------------------------------------------\n");
    }

    // [5] 최종 성능 비교
    printf("=== [4] Performance Summary ===\n");
    printf("Searches : %d\n\n", SEARCH_SIZE);

    printf("Sequential Search\n");
    printf("Total comparisons   : %d\n", seqTotalComps);
    printf("Average comparisons : %.2f\n\n", (double)seqTotalComps / SEARCH_SIZE);

    printf("BST Search\n");
    printf("Total comparisons   : %d\n", bstTotalComps);
    printf("Average comparisons : %.2f\n\n", (double)bstTotalComps / SEARCH_SIZE);

    printf("AVL Search\n");
    printf("Total comparisons   : %d\n", avlTotalComps);
    printf("Average comparisons : %.2f\n\n", (double)avlTotalComps / SEARCH_SIZE);

    // 메모리 해제
    freeTree(bstRoot);
    freeTree(avlRoot);

    return 0;
}