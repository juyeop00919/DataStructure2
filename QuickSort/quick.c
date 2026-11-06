#include "quick.h"

// 데이터 생성 (0 ~ 99999 사이의 무작위 정수)
void generate_data(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

// 배열 복사 (동일한 데이터로 테스트하기 위함)
void copy_array(int* src, int* dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 정렬 검증 (오름차순 확인)
int verify_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return 0; // 정렬 실패
    }
    return 1;
}

// 공통 분할(Partition) 함수
// 인덱스 및 반복문 조건은 제외하고 데이터 값 비교만 측정
int partition(int* arr, int left, int right, long long* cmp_count) {
    int pivot = arr[left];
    int i = left;
    int j = right + 1;

    while (1) {
        do {
            i++;
            if (i <= right) {
                (*cmp_count)++; // arr[i]와 pivot 비교
            }
        } while (i <= right && arr[i] < pivot);

        do {
            j--;
            (*cmp_count)++; // arr[j]와 pivot 비교
        } while (arr[j] > pivot);

        if (i >= j) break;
        swap(&arr[i], &arr[j]);
    }
    swap(&arr[left], &arr[j]);
    return j;
}

// [1] 첫 번째 원소 피벗
void quick_sort_first(int* arr, int left, int right, long long* cmp_count) {
    if (left < right) {
        int p = partition(arr, left, right, cmp_count);
        quick_sort_first(arr, left, p - 1, cmp_count);
        quick_sort_first(arr, p + 1, right, cmp_count);
    }
}

// [2] 무작위 원소 피벗
void quick_sort_random(int* arr, int left, int right, long long* cmp_count) {
    if (left < right) {
        int rand_idx = left + rand() % (right - left + 1);
        swap(&arr[left], &arr[rand_idx]); // 선택한 피벗을 제일 앞으로 이동

        int p = partition(arr, left, right, cmp_count);
        quick_sort_random(arr, left, p - 1, cmp_count);
        quick_sort_random(arr, p + 1, right, cmp_count);
    }
}

// 세 원소의 중앙값 찾기 (비교 횟수 포함)
int median_of_three(int* arr, int left, int right, long long* cmp_count) {
    int mid = left + (right - left) / 2;
    int a = left, b = mid, c = right;

    (*cmp_count)++;
    if (arr[a] > arr[b]) {
        (*cmp_count)++;
        if (arr[b] > arr[c]) return b;
        (*cmp_count)++;
        if (arr[a] > arr[c]) return c;
        return a;
    }
    else {
        (*cmp_count)++;
        if (arr[a] > arr[c]) return a;
        (*cmp_count)++;
        if (arr[b] > arr[c]) return c;
        return b;
    }
}

// [3] 세 원소 중앙값 피벗
void quick_sort_median3(int* arr, int left, int right, long long* cmp_count) {
    if (left < right) {
        if (right - left >= 2) {
            int med_idx = median_of_three(arr, left, right, cmp_count);
            swap(&arr[left], &arr[med_idx]); // ✅ 수정 완료
        }
        int p = partition(arr, left, right, cmp_count);
        quick_sort_median3(arr, left, p - 1, cmp_count);
        quick_sort_median3(arr, p + 1, right, cmp_count);
    }
}

// --- 아래는 보너스 과제용 (실행시간 측정) ---

// 재귀적 퀵 정렬 (Median-of-Three 적용, 카운트 제외)
void quick_sort_recursive(int* arr, int left, int right) {
    long long dummy = 0; // 측정 안 함
    if (left < right) {
        if (right - left >= 2) {
            int med_idx = median_of_three(arr, left, right, &dummy);
            swap(&arr[left], &arr[med_idx]); // ✅ 수정 완료
        }
        int p = partition(arr, left, right, &dummy);
        quick_sort_recursive(arr, left, p - 1);
        quick_sort_recursive(arr, p + 1, right);
    }
}

// 스택을 이용한 반복적 퀵 정렬 (Median-of-Three 적용)
void quick_sort_iterative(int* arr, int left, int right) {
    int* stack = (int*)malloc((right - left + 1) * sizeof(int));
    int top = -1;
    long long dummy = 0; // 카운트 제외

    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        int r = stack[top--];
        int l = stack[top--];

        if (l < r) {
            if (r - l >= 2) {
                int med_idx = median_of_three(arr, l, r, &dummy);
                swap(&arr[l], &arr[med_idx]); 
            }
            int p = partition(arr, l, r, &dummy);

            // 좌측 부분 배열 푸시
            if (p - 1 > l) {
                stack[++top] = l;
                stack[++top] = p - 1;
            }
            // 우측 부분 배열 푸시
            if (p + 1 < r) {
                stack[++top] = p + 1;
                stack[++top] = r;
            }
        }
    }
    free(stack);
}