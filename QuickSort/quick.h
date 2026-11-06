#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 데이터 생성 및 유틸리티 함수
void generate_data(int* arr, int n);
void copy_array(int* src, int* dest, int n);
void swap(int* a, int* b);
int verify_sort(int* arr, int n);

// 피벗 선택 방법에 따른 퀵 정렬 (비교 횟수 측정용)
void quick_sort_first(int* arr, int left, int right, long long* cmp_count);
void quick_sort_random(int* arr, int left, int right, long long* cmp_count);
void quick_sort_median3(int* arr, int left, int right, long long* cmp_count);

// 보너스: 반복적 퀵 정렬
void quick_sort_iterative(int* arr, int left, int right);
// 보너스: 재귀적 퀵 정렬
void quick_sort_recursive(int* arr, int left, int right);
