#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merge.h"

// =====================================================================
// 메모리 계산용 스택 프레임 크기 동적 계산 (sizeof 활용)
// 1. Merge Sort 재귀 인자: 포인터 4개 (arr, temp, comp, max_depth) + 정수 3개 (left, right, depth)
#define MERGE_FRAME_SIZE (4 * sizeof(void*) + 3 * sizeof(int))
// 2. Quick Sort 재귀 인자: 포인터 3개 (arr, comp, max_depth) + 정수 3개 (low, high, depth)
#define QUICK_FRAME_SIZE (3 * sizeof(void*) + 3 * sizeof(int))
// =====================================================================

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ---------------------------------------------------------
// 1. 병합 정렬 (Merge Sort)
// ---------------------------------------------------------
void merge(int* arr, int* temp, int left, int mid, int right, unsigned long long* comp) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        (*comp)++;
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left; i <= right; i++) arr[i] = temp[i];
}

void merge_sort_recursive(int* arr, int* temp, int left, int right, int depth, unsigned long long* comp, int* max_depth) {
    if (depth > *max_depth) *max_depth = depth;
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(arr, temp, left, mid, depth + 1, comp, max_depth);
        merge_sort_recursive(arr, temp, mid + 1, right, depth + 1, comp, max_depth);
        merge(arr, temp, left, mid, right, comp);
    }
}

SortStats run_merge_sort(int* test_arr, int* original_arr, int n, int iterations) {
    SortStats stats = { 0, 0.0, 0 };
    int* temp = (int*)malloc(n * sizeof(int));
    int global_max_depth = 0;
    clock_t total_time = 0;
    unsigned long long total_comparisons = 0;

    for (int i = 0; i < iterations; i++) {
        memcpy(test_arr, original_arr, n * sizeof(int));
        unsigned long long comp = 0;
        int max_depth = 0;

        clock_t start = clock();
        merge_sort_recursive(test_arr, temp, 0, n - 1, 1, &comp, &max_depth);
        clock_t end = clock();

        total_time += (end - start);
        total_comparisons += comp;
        if (max_depth > global_max_depth) global_max_depth = max_depth;
    }

    stats.time_ms = ((double)total_time / CLOCKS_PER_SEC * 1000.0) / iterations;
    stats.comparisons = total_comparisons / iterations;
    // 동적 할당 메모리(n * sizeof(int)) + 재귀 호출 스택 메모리(max_depth * sizeof 기반 프레임 크기)
    stats.memory_bytes = (n * sizeof(int)) + (global_max_depth * MERGE_FRAME_SIZE);

    free(temp);
    return stats;
}

// ---------------------------------------------------------
// 2. 퀵 정렬 (Quick Sort) 공통 분할 로직
// ---------------------------------------------------------
int partition(int* arr, int low, int high, unsigned long long* comp) {
    int pivot = arr[low];
    int i = low;
    for (int j = low + 1; j <= high; j++) {
        (*comp)++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[i]);
    return i;
}

// ---------------------------------------------------------
// 퀵 정렬 - (1) First Element
// ---------------------------------------------------------
void quick_sort_first(int* arr, int low, int high, int depth, unsigned long long* comp, int* max_depth) {
    if (depth > *max_depth) *max_depth = depth;
    if (low < high) {
        int pi = partition(arr, low, high, comp);
        quick_sort_first(arr, low, pi - 1, depth + 1, comp, max_depth);
        quick_sort_first(arr, pi + 1, high, depth + 1, comp, max_depth);
    }
}

SortStats run_quick_sort_first(int* test_arr, int* original_arr, int n, int iterations) {
    SortStats stats = { 0, 0.0, 0 };
    int global_max_depth = 0;
    clock_t total_time = 0;
    unsigned long long total_comparisons = 0;

    for (int i = 0; i < iterations; i++) {
        memcpy(test_arr, original_arr, n * sizeof(int));
        unsigned long long comp = 0;
        int max_depth = 0;

        clock_t start = clock();
        quick_sort_first(test_arr, 0, n - 1, 1, &comp, &max_depth);
        clock_t end = clock();

        total_time += (end - start);
        total_comparisons += comp;
        if (max_depth > global_max_depth) global_max_depth = max_depth;
    }

    stats.time_ms = ((double)total_time / CLOCKS_PER_SEC * 1000.0) / iterations;
    stats.comparisons = total_comparisons / iterations;
    stats.memory_bytes = global_max_depth * QUICK_FRAME_SIZE;
    return stats;
}

// ---------------------------------------------------------
// 퀵 정렬 - (2) Random Pivot
// ---------------------------------------------------------
void quick_sort_random(int* arr, int low, int high, int depth, unsigned long long* comp, int* max_depth) {
    if (depth > *max_depth) *max_depth = depth;
    if (low < high) {
        int random_idx = low + rand() % (high - low + 1);
        swap(&arr[low], &arr[random_idx]);

        int pi = partition(arr, low, high, comp);
        quick_sort_random(arr, low, pi - 1, depth + 1, comp, max_depth);
        quick_sort_random(arr, pi + 1, high, depth + 1, comp, max_depth);
    }
}

SortStats run_quick_sort_random(int* test_arr, int* original_arr, int n, int iterations) {
    SortStats stats = { 0, 0.0, 0 };
    int global_max_depth = 0;
    clock_t total_time = 0;
    unsigned long long total_comparisons = 0;

    for (int i = 0; i < iterations; i++) {
        memcpy(test_arr, original_arr, n * sizeof(int));
        unsigned long long comp = 0;
        int max_depth = 0;

        clock_t start = clock();
        quick_sort_random(test_arr, 0, n - 1, 1, &comp, &max_depth);
        clock_t end = clock();

        total_time += (end - start);
        total_comparisons += comp;
        if (max_depth > global_max_depth) global_max_depth = max_depth;
    }

    stats.time_ms = ((double)total_time / CLOCKS_PER_SEC * 1000.0) / iterations;
    stats.comparisons = total_comparisons / iterations;
    stats.memory_bytes = global_max_depth * QUICK_FRAME_SIZE;
    return stats;
}

// ---------------------------------------------------------
// 퀵 정렬 - (3) Median-of-Three
// ---------------------------------------------------------
void quick_sort_median3(int* arr, int low, int high, int depth, unsigned long long* comp, int* max_depth) {
    if (depth > *max_depth) *max_depth = depth;
    if (low < high) {
        int mid = low + (high - low) / 2;
        int a = arr[low], b = arr[mid], c = arr[high];
        int pivot_idx;

        (*comp)++;
        if (a > b) {
            (*comp)++;
            if (b > c) pivot_idx = mid;
            else {
                (*comp)++;
                if (a > c) pivot_idx = high; else pivot_idx = low;
            }
        }
        else {
            (*comp)++;
            if (a > c) pivot_idx = low;
            else {
                (*comp)++;
                if (b > c) pivot_idx = high; else pivot_idx = mid;
            }
        }
        swap(&arr[low], &arr[pivot_idx]);

        int pi = partition(arr, low, high, comp);
        quick_sort_median3(arr, low, pi - 1, depth + 1, comp, max_depth);
        quick_sort_median3(arr, pi + 1, high, depth + 1, comp, max_depth);
    }
}

SortStats run_quick_sort_median3(int* test_arr, int* original_arr, int n, int iterations) {
    SortStats stats = { 0, 0.0, 0 };
    int global_max_depth = 0;
    clock_t total_time = 0;
    unsigned long long total_comparisons = 0;

    for (int i = 0; i < iterations; i++) {
        memcpy(test_arr, original_arr, n * sizeof(int));
        unsigned long long comp = 0;
        int max_depth = 0;

        clock_t start = clock();
        quick_sort_median3(test_arr, 0, n - 1, 1, &comp, &max_depth);
        clock_t end = clock();

        total_time += (end - start);
        total_comparisons += comp;
        if (max_depth > global_max_depth) global_max_depth = max_depth;
    }

    stats.time_ms = ((double)total_time / CLOCKS_PER_SEC * 1000.0) / iterations;
    stats.comparisons = total_comparisons / iterations;
    stats.memory_bytes = global_max_depth * QUICK_FRAME_SIZE;
    return stats;
}

// ---------------------------------------------------------
// 유효성 검증 함수
// ---------------------------------------------------------
int is_sorted(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return 0;
    }
    return 1;
}