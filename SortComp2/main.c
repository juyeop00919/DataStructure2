#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

int main() {
    // 요구사항에 따른 데이터 크기 배열
    int sizes[] = { 1000, 2000, 4000, 8000, 16000, 20000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    srand((unsigned int)time(NULL));

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int* original = (int*)malloc(n * sizeof(int));
        int* testArr = (int*)malloc(n * sizeof(int));

        // 1. 무작위 원본 데이터 생성
        for (int i = 0; i < n; i++) {
            original[i] = rand();
        }

        printf("Data Size : %d\n\n", n);

        // [1] 삽입 정렬
        copyArray(original, testArr, n);
        unsigned long long cmp_insert = insertionSort(testArr, n);
        if (!isSorted(testArr, n)) printf("Error: Insertion Sort Failed.\n");

        // [2] 쉘 정렬 - 기본 간격
        copyArray(original, testArr, n);
        unsigned long long cmp_shell_orig = shellSortOriginal(testArr, n);
        if (!isSorted(testArr, n)) printf("Error: Shell Sort (Original) Failed.\n");

        // [3] 쉘 정렬 - Knuth 간격 수열
        copyArray(original, testArr, n);
        unsigned long long cmp_shell_knuth = shellSortKnuth(testArr, n);
        if (!isSorted(testArr, n)) printf("Error: Shell Sort (Knuth) Failed.\n");

        // 출력 형식에 맞추어 결과 출력
        printf("Insertion Sort       : %llu comparisons\n", cmp_insert);
        printf("Shell Sort (Original): %llu comparisons\n", cmp_shell_orig);
        printf("Shell Sort (Knuth)   : %llu comparisons\n", cmp_shell_knuth);
        printf("\n");

        // 메모리 해제
        free(original);
        free(testArr);
    }

    return 0;
}