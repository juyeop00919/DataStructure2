#include "sort.h"

// [1] 삽입 정렬 (Insertion Sort)
unsigned long long insertionSort(int arr[], int n) {
    unsigned long long cmp_count = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i;

        while (j > 0) {
            cmp_count++; 
            if (arr[j - 1] > key) {
                arr[j] = arr[j - 1];
                j--;
            }
            else {
                break;
            }
        }
        arr[j] = key;
    }

    return cmp_count;
}

// [2] 쉘 정렬 - 기본 간격 (Original Sequence)
unsigned long long shellSortOriginal(int arr[], int n) {
    unsigned long long cmp_count = 0;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i;

            while (j >= gap) {
                cmp_count++; 
                if (arr[j - gap] > key) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                else {
                    break;
                }
            }
            arr[j] = key;
        }
    }

    return cmp_count;
}

// [3] 쉘 정렬 - Knuth 간격 수열 (Knuth Sequence)
unsigned long long shellSortKnuth(int arr[], int n) {
    unsigned long long cmp_count = 0;
    int gap = 1;

    while (gap < n) {
        gap = gap * 3 + 1;
    }
    gap = (gap - 1) / 3; 

    for (; gap > 0; gap = (gap - 1) / 3) {
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i;

            while (j >= gap) {
                cmp_count++; 
                if (arr[j - gap] > key) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                else {
                    break;
                }
            }
            arr[j] = key;
        }
    }

    return cmp_count;
}

// 배열 복사 유틸리티
void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// 오름차순 정렬 검증 유틸리티
int isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return 0; // 정렬 실패
        }
    }
    return 1; // 정렬 성공
}