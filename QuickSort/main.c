#include "quick.h"

// 보너스 과제 테스트 함수 (main.c)
void run_bonus_test() {
    int n = 10000;
    int iter = 100;
    int* original = (int*)malloc(n * sizeof(int));
    generate_data(original, n);

    // 1. 과제 조건(배열 복사 시간 제외)을 맞추기 위해 미리 100개의 복사본 생성
    int** copies_rec = (int**)malloc(iter * sizeof(int*));
    int** copies_iter = (int**)malloc(iter * sizeof(int*));

    for (int i = 0; i < iter; i++) {
        copies_rec[i] = (int*)malloc(n * sizeof(int));
        copies_iter[i] = (int*)malloc(n * sizeof(int));
        copy_array(original, copies_rec[i], n);
        copy_array(original, copies_iter[i], n);
    }

    clock_t start, end;
    double time_rec_total = 0, time_iter_total = 0;

    // 2. 재귀적 퀵 정렬 (시작 -> 100번 정렬 -> 끝)
    start = clock();
    for (int i = 0; i < iter; i++) {
        quick_sort_recursive(copies_rec[i], 0, n - 1);
    }
    end = clock();
    time_rec_total = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

    // 3. 반복적 퀵 정렬 (시작 -> 100번 정렬 -> 끝)
    start = clock();
    for (int i = 0; i < iter; i++) {
        quick_sort_iterative(copies_iter[i], 0, n - 1);
    }
    end = clock();
    time_iter_total = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

    // 4. 결과 출력
    printf("Data Size : %d\n", n);
    printf("Pivot     : Median-of-Three\n");
    printf("Test Runs : %d times (Total Time)\n\n", iter);

    printf("Recursive Quick Sort : %.4f ms\n", time_rec_total);
    printf("Iterative Quick Sort : %.4f ms\n\n", time_iter_total);

    // 5. 메모리 해제
    for (int i = 0; i < iter; i++) {
        free(copies_rec[i]);
        free(copies_iter[i]);
    }
    free(copies_rec);
    free(copies_iter);
    free(original);
}
int main() {
    srand((unsigned int)time(NULL));

    int sizes[] = { 1000, 2000, 4000, 8000, 16000, 20000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* original = (int*)malloc(n * sizeof(int));
        int* arr = (int*)malloc(n * sizeof(int));

        generate_data(original, n);

        long long cmp_first = 0;
        long long cmp_random = 0;
        long long cmp_median = 0;

        // 1. First Element
        copy_array(original, arr, n);
        quick_sort_first(arr, 0, n - 1, &cmp_first);
        if (!verify_sort(arr, n)) printf("First Element Fail\n");

        // 2. Random Pivot
        copy_array(original, arr, n);
        quick_sort_random(arr, 0, n - 1, &cmp_random);
        if (!verify_sort(arr, n)) printf("Random Pivot Fail\n");

        // 3. Median-of-Three
        copy_array(original, arr, n);
        quick_sort_median3(arr, 0, n - 1, &cmp_median);
        if (!verify_sort(arr, n)) printf("Median-of-Three Fail\n");

        // 결과 출력
        printf("Data Size : %d\n\n", n);
        printf("Quick Sort (First)    : %lld comparisons\n", cmp_first);
        printf("Quick Sort (Random)   : %lld comparisons\n", cmp_random);
        printf("Quick Sort (Median-3) : %lld comparisons\n\n", cmp_median);

        free(original);
        free(arr);
    }

    printf("--------------------------------------\n");
    printf("[Bonus] Recursive vs Iterative\n");
    printf("--------------------------------------\n");
    run_bonus_test();

    return 0;
}