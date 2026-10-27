#ifndef SORT_H
#define SORT_H

#define MAX_VAL 1000000
#define DATA_SIZE 10000
#define RANDOM_TRIALS 100

// 데이터 구조체
typedef struct {
    int key1;
    int key2;
    int id; // 안정성 검증을 위한 원래 입력 순서
} Data;

// 성능 측정용 구조체
typedef struct {
    unsigned long long comps;
    unsigned long long moves;
} Stats;

// 정렬 함수
void selection_sort(Data* arr, int n, Stats* stats);
void bubble_sort(Data* arr, int n, Stats* stats);
void bubble_sort_early(Data* arr, int n, Stats* stats);
void insertion_sort_gt(Data* arr, int n, Stats* stats); // case A: >
void insertion_sort_ge(Data* arr, int n, Stats* stats); // case B: >=

// 유틸리티 함수
void generate_random_data(Data* arr, int n);
void generate_sorted_data(Data* arr, int n);
void generate_reverse_data(Data* arr, int n);
void generate_partially_sorted_data(Data* arr, int n);
int is_sorted(Data* arr, int n);
int check_stability(Data* arr, int n);
void copy_data(Data* dest, Data* src, int n);

#endif