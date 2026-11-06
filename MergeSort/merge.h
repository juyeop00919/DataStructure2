#ifndef MERGE_H
#define MERGE_H

// 성능 측정 결과를 저장할 구조체
typedef struct {
    unsigned long long comparisons;
    double time_ms;
    unsigned long long memory_bytes;
} SortStats;

// 알고리즘 실행 및 측정 래퍼 함수들
SortStats run_merge_sort(int* test_arr, int* original_arr, int n, int iterations);
SortStats run_quick_sort_first(int* test_arr, int* original_arr, int n, int iterations);
SortStats run_quick_sort_random(int* test_arr, int* original_arr, int n, int iterations);
SortStats run_quick_sort_median3(int* test_arr, int* original_arr, int n, int iterations);

// 정렬 검증용 함수
int is_sorted(int* arr, int n);

#endif