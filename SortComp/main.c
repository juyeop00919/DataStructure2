#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

void run_random_experiments() {
    Stats total_sel = { 0 }, total_bub = { 0 }, total_bub_e = { 0 }, total_ins = { 0 };

    Data* original = (Data*)malloc(sizeof(Data) * DATA_SIZE);
    Data* temp = (Data*)malloc(sizeof(Data) * DATA_SIZE);

    for (int t = 0; t < RANDOM_TRIALS; t++) {
        generate_random_data(original, DATA_SIZE);

        Stats st;

        copy_data(temp, original, DATA_SIZE); st.comps = 0; st.moves = 0;
        selection_sort(temp, DATA_SIZE, &st);
        total_sel.comps += st.comps; total_sel.moves += st.moves;

        copy_data(temp, original, DATA_SIZE); st.comps = 0; st.moves = 0;
        bubble_sort(temp, DATA_SIZE, &st);
        total_bub.comps += st.comps; total_bub.moves += st.moves;

        copy_data(temp, original, DATA_SIZE); st.comps = 0; st.moves = 0;
        bubble_sort_early(temp, DATA_SIZE, &st);
        total_bub_e.comps += st.comps; total_bub_e.moves += st.moves;

        copy_data(temp, original, DATA_SIZE); st.comps = 0; st.moves = 0;
        insertion_sort_gt(temp, DATA_SIZE, &st);
        total_ins.comps += st.comps; total_ins.moves += st.moves;
    }

    printf("Data Count : %d\n\n", DATA_SIZE);
    printf("Random Data\n");
    printf("Number of Trials : %d\n\n", RANDOM_TRIALS);

    printf("Selection Sort\n");
    printf("Total Comparisons   : %llu\n", total_sel.comps);
    printf("Average Comparisons : %llu\n", total_sel.comps / RANDOM_TRIALS);
    printf("Average Movements   : %llu\n\n", total_sel.moves / RANDOM_TRIALS);

    printf("Bubble Sort\n");
    printf("Total Comparisons   : %llu\n", total_bub.comps);
    printf("Average Comparisons : %llu\n", total_bub.comps / RANDOM_TRIALS);
    printf("Average Movements   : %llu\n\n", total_bub.moves / RANDOM_TRIALS);

    printf("Bubble Sort (Early Termination)\n");
    printf("Total Comparisons   : %llu\n", total_bub_e.comps);
    printf("Average Comparisons : %llu\n", total_bub_e.comps / RANDOM_TRIALS);
    printf("Average Movements   : %llu\n\n", total_bub_e.moves / RANDOM_TRIALS);

    printf("Insertion Sort\n");
    printf("Total Comparisons   : %llu\n", total_ins.comps);
    printf("Average Comparisons : %llu\n", total_ins.comps / RANDOM_TRIALS);
    printf("Average Movements   : %llu\n\n", total_ins.moves / RANDOM_TRIALS);
    printf("------------------------------------\n\n");

    free(original);
    free(temp);
}

void test_specific_state(const char* state_name, void (*gen_func)(Data*, int)) {
    Data* original = (Data*)malloc(sizeof(Data) * DATA_SIZE);
    Data* temp = (Data*)malloc(sizeof(Data) * DATA_SIZE);

    gen_func(original, DATA_SIZE);
    printf("%s\n\n", state_name);

    Stats st;

    copy_data(temp, original, DATA_SIZE); st.comps = 0; st.moves = 0;
    selection_sort(temp, DATA_SIZE, &st);
    printf("Selection Sort\nComparisons : %llu\nMovements   : %llu\n\n", st.comps, st.moves);

    copy_data(temp, original, DATA_SIZE); st.comps = 0; st.moves = 0;
    bubble_sort(temp, DATA_SIZE, &st);
    printf("Bubble Sort\nComparisons : %llu\nMovements   : %llu\n\n", st.comps, st.moves);

    copy_data(temp, original, DATA_SIZE); st.comps = 0; st.moves = 0;
    bubble_sort_early(temp, DATA_SIZE, &st);
    printf("Bubble Sort (Early Termination)\nComparisons : %llu\nMovements   : %llu\n\n", st.comps, st.moves);

    copy_data(temp, original, DATA_SIZE); st.comps = 0; st.moves = 0;
    insertion_sort_gt(temp, DATA_SIZE, &st);
    printf("Insertion Sort\nComparisons : %llu\nMovements   : %llu\n\n", st.comps, st.moves);
    printf("------------------------------------\n\n");

    free(original);
    free(temp);
}

void test_stability() {
    // 안정성 테스트를 위한 의도적인 데이터 생성 (중복 키 포함)
    int n = 1000;
    Data* original = (Data*)malloc(sizeof(Data) * n);
    Data* temp = (Data*)malloc(sizeof(Data) * n);

    for (int i = 0; i < n; i++) {
        original[i].key1 = rand() % 50;
        original[i].key2 = rand() % MAX_VAL;
        original[i].id = i;
    }

    printf("Stability Verification\n\n");
    Stats st;

    copy_data(temp, original, n);
    selection_sort(temp, n, &st);
    printf("Selection Sort       : %s\n", check_stability(temp, n) ? "Stable" : "Unstable");

    copy_data(temp, original, n);
    bubble_sort(temp, n, &st);
    printf("Bubble Sort          : %s\n", check_stability(temp, n) ? "Stable" : "Unstable");

    copy_data(temp, original, n);
    insertion_sort_gt(temp, n, &st);
    printf("Insertion Sort (>)   : %s\n", check_stability(temp, n) ? "Stable" : "Unstable");

    copy_data(temp, original, n);
    insertion_sort_ge(temp, n, &st);
    printf("Insertion Sort (>=)  : %s\n", check_stability(temp, n) ? "Stable" : "Unstable");

    free(original);
    free(temp);
}

int main() {
    srand((unsigned int)time(NULL));

    run_random_experiments();
    test_specific_state("Sorted Data", generate_sorted_data);
    test_specific_state("Reverse-Sorted Data", generate_reverse_data);
    test_specific_state("Partially Sorted Data", generate_partially_sorted_data);
    test_stability();

    return 0;
}