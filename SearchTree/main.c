#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "SearchTree.h"

#define DATA_SIZE 100
#define SEARCH_SIZE 50
#define MAX_VAL 1000

bool isDuplicate(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

//순차 탐색 횟수
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
    int arr[DATA_SIZE];
    int searchKeys[SEARCH_SIZE];
    TreeNode* bstRoot = NULL;
    int bstCreationComps = 0;

    srand((unsigned int)time(NULL));

    // 100개의 데이터 생성 
    printf("=== [1] Generated %d Unique Numbers ===\n", DATA_SIZE);
    for (int i = 0; i < DATA_SIZE; i++) {
        int temp;
        do {
            temp = rand() % (MAX_VAL + 1); // 0 ~ 1000 임의의 정수
		} while (isDuplicate(arr, i, temp)); //중복시 다시 생성

        arr[i] = temp;
        bstRoot = insertNode(bstRoot, temp, &bstCreationComps); //트리 삽입

        printf("%d ", arr[i]);
        if ((i + 1) % 20 == 0) printf("\n");
    }
    printf("\nTotal Comparisons during BST Creation: %d\n\n", bstCreationComps);
    
    //BST 내부 데이터 출력 
    //printf("\n=== [1-1] BST Internal Data ===\n");
    //printInorder(bstRoot);
    //printf("\n\n");

    //printf("\n=== [1-2] BST Visual Structure ===\n");
    //printTree(bstRoot, 0);
    //printf("\n\n");

    // 탐색 대상 랜덤 생성  
    printf("=== [2] Generated %d Search Keys ===\n", SEARCH_SIZE);
    for (int i = 0; i < SEARCH_SIZE; i++) {
        searchKeys[i] = rand() % (MAX_VAL + 1);
        printf("%d ", searchKeys[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");

    // 통계용 변수
    int seqTotalComps = 0; //순차탐색
    int bstTotalComps = 0; //BST탐색 

    //결과 출력
    printf("=== [3] Search Results ===\n");
    for (int i = 0; i < SEARCH_SIZE; i++) {
        int target = searchKeys[i];
        int seqComps = 0;
        int bstComps = 0;

        bool seqResult = sequentialSearch(arr, DATA_SIZE, target, &seqComps);
        bool bstResult = bstSearch(bstRoot, target, &bstComps);

        seqTotalComps += seqComps;
        bstTotalComps += bstComps;

        printf("Search Key : %d\n\n", target);

        printf("Sequential Search\n");
        printf("Result      : %s\n", seqResult ? "Found" : "Not Found");
        printf("Comparisons : %d\n\n", seqComps);

        printf("BST Search\n");
        printf("Result      : %s\n", bstResult ? "Found" : "Not Found");
        printf("Comparisons : %d\n", bstComps);
        printf("--------------------------------------------------\n");
    }

    // 최종 성능 비교
    printf("=== [4] Performance Summary ===\n");
    printf("Number of searches: %d\n\n", SEARCH_SIZE);

    printf("Sequential Search\n");
    printf("Total comparisons   : %d\n", seqTotalComps);
    printf("Average comparisons : %.2f\n\n", (double)seqTotalComps / SEARCH_SIZE);

    printf("BST Search\n");
    printf("Total comparisons   : %d\n", bstTotalComps);
    printf("Average comparisons : %.2f\n\n", (double)bstTotalComps / SEARCH_SIZE);

    printf("Note: BST Creation Cost (Comparisons) was %d.\n", bstCreationComps);

    // 메모리 해제
    freeTree(bstRoot);

    return 0;
}