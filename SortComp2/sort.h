#pragma once
// 정렬 알고리즘 선언
unsigned long long insertionSort(int arr[], int n);
unsigned long long shellSortOriginal(int arr[], int n);
unsigned long long shellSortKnuth(int arr[], int n);

// 유틸리티 함수 선언
void copyArray(int src[], int dest[], int n);
int isSorted(int arr[], int n);
