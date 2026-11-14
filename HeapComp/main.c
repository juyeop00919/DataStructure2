#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge.h"

// 1000번 반복 실행하여 평균 시간 측정
#define ITERATIONS 1000 

void print_stats(const char* name, SortStats stats) {
    printf("%-15s %-14llu %-11.4f %-15llu\n", name, stats.comparisons, stats.time_ms, stats.memory_bytes);
}

int main() {
    int sizes[] = { 1000, 2000, 4000, 8000, 16000, 20000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    srand((unsigned int)time(NULL));

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];

        int* original_arr = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            original_arr[j] = rand() % 100000;
        }

        int* test_arr = (int*)malloc(n * sizeof(int));
        SortStats stats;

        printf("Data Size : %d\n\n", n);
        printf("%-15s %-14s %-11s %-15s\n", "Algorithm", "Comparisons", "Time(ms)", "Memory(Bytes)");
        printf("--------------------------------------------------------\n");

        stats = run_heap_sort(test_arr, original_arr, n, ITERATIONS);
        print_stats("Heap Sort", stats);
        if (!is_sorted(test_arr, n)) printf("  [!] Heap Sort failed!\n");

        stats = run_merge_sort(test_arr, original_arr, n, ITERATIONS);
        print_stats("Merge Sort", stats);
        if (!is_sorted(test_arr, n)) printf("  [!] Merge Sort failed!\n");

        stats = run_quick_sort_first(test_arr, original_arr, n, ITERATIONS);
        print_stats("Quick (First)", stats);
        if (!is_sorted(test_arr, n)) printf("  [!] Quick (First) failed!\n");

        stats = run_quick_sort_random(test_arr, original_arr, n, ITERATIONS);
        print_stats("Quick (Random)", stats);
        if (!is_sorted(test_arr, n)) printf("  [!] Quick (Random) failed!\n");

        stats = run_quick_sort_median3(test_arr, original_arr, n, ITERATIONS);
        print_stats("Quick (Median3)", stats);
        if (!is_sorted(test_arr, n)) printf("  [!] Quick (Median3) failed!\n");

        printf("\n");

        free(original_arr);
        free(test_arr);
    }

    return 0;
}