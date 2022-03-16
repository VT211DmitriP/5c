#include <stdlib.h>
#include <stdio.h>

#ifndef INC_5C_COMPLEXITYASSESSMENT_SORTS_H
#define INC_5C_COMPLEXITYASSESSMENT_SORTS_H

void swap(int *a, int *b);

int compare_ints(const void *a, const void *b);

int compare_intsReverse(const void *a, const void *b);

void bubbleSort(int *a, size_t size);

void selectionSort(int *a, const size_t size);

void insertionSort(int *a, const size_t size);

void combSort(int *a, const size_t size);

void shellSort(int *arr, size_t size);

void radixSort(int *a, size_t n);

long long getBubbleSortNComp(int *a, size_t n);

long long getSelectionSortNComp(int *a, size_t n);

long long getInsertionSortNComp(int *a, size_t n);

long long getCombSortNComp(int *a, size_t n);

long long getShellSortNComp(int *a, size_t n);

long long getRadixSortNComps(int *a, size_t n);

#endif
