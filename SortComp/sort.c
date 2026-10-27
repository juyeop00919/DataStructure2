#include "sort.h"
#include <stdlib.h>
#include <string.h>

void selection_sort(Data* arr, int n, Stats* stats) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            stats->comps++;
            if (arr[j].key1 < arr[min_idx].key1) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Data temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            stats->moves += 3;
        }
    }
}

void bubble_sort(Data* arr, int n, Stats* stats) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            stats->comps++;
            if (arr[j].key1 > arr[j + 1].key1) {
                Data temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                stats->moves += 3;
            }
        }
    }
}

void bubble_sort_early(Data* arr, int n, Stats* stats) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            stats->comps++;
            if (arr[j].key1 > arr[j + 1].key1) {
                Data temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                stats->moves += 3;
                swapped = 1;
            }
        }
        if (!swapped) break; // 조기 종료
    }
}

void insertion_sort_gt(Data* arr, int n, Stats* stats) {
    for (int i = 1; i < n; i++) {
        Data key = arr[i];
        stats->moves++; // key 변수에 복사

        int j = i - 1;
        while (j >= 0) {
            stats->comps++;
            if (arr[j].key1 > key.key1) {
                arr[j + 1] = arr[j];
                stats->moves++; // 데이터 이동
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
        stats->moves++; // 최종 위치에 삽입
    }
}

void insertion_sort_ge(Data* arr, int n, Stats* stats) {
    for (int i = 1; i < n; i++) {
        Data key = arr[i];
        stats->moves++;

        int j = i - 1;
        while (j >= 0) {
            stats->comps++;
            if (arr[j].key1 >= key.key1) {
                arr[j + 1] = arr[j];
                stats->moves++;
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
        stats->moves++;
    }
}

// ---------------- 유틸리티 구현 ----------------

void generate_random_data(Data* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i].key1 = rand() % (MAX_VAL + 1);
        arr[i].key2 = rand() % (MAX_VAL + 1);
        arr[i].id = i;
    }
}

// 오름차순
int compare_asc(const void* a, const void* b) {
    return ((Data*)a)->key1 - ((Data*)b)->key1;
}

// 내림차순
int compare_desc(const void* a, const void* b) {
    return ((Data*)b)->key1 - ((Data*)a)->key1;
}

void generate_sorted_data(Data* arr, int n) {
    generate_random_data(arr, n);
    qsort(arr, n, sizeof(Data), compare_asc);
    for (int i = 0; i < n; i++) arr[i].id = i; // id 재설정
}

void generate_reverse_data(Data* arr, int n) {
    generate_random_data(arr, n);
    qsort(arr, n, sizeof(Data), compare_desc);
    for (int i = 0; i < n; i++) arr[i].id = i;
}

void generate_partially_sorted_data(Data* arr, int n) {
    generate_sorted_data(arr, n);
    // 5%의 원소 위치를 무작위로 교환하여 부분 정렬 상태 생성
    int swaps = n * 0.05;
    for (int i = 0; i < swaps; i++) {
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        Data temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

int is_sorted(Data* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i].key1 > arr[i + 1].key1) return 0;
    }
    return 1;
}

int check_stability(Data* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i].key1 == arr[i + 1].key1) {
            if (arr[i].id > arr[i + 1].id) return 0; // 원래 순서가 뒤집히면 Unstable
        }
    }
    return 1;
}

void copy_data(Data* dest, Data* src, int n) {
    memcpy(dest, src, sizeof(Data) * n);
}