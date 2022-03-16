#include "sorts.h"
#include <memory.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int compare_intsReverse(const void *a, const void *b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;

    if (arg1 > arg2) return -1;
    if (arg1 < arg2) return 1;
    return 0;
}

void bubbleSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = size - 1; j > i; j--)
            if (a[j - 1] > a[j])
                swap(&a[j - 1], &a[j]);
}

void selectionSort(int *a, const size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < size; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos]);
    }
}

void insertionSort(int *a, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void combSort(int *a, const size_t size) {
    size_t step = size;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
}

void shellSort(int *a, size_t size) {
    for (size_t step = size / 2; step > 0; step /= 2)
        for (size_t i = step; i < size; i++) {
            int tmp = a[i];
            size_t j;
            for (j = i; j >= step; j -= step) {
                if (tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }
}

int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

void radixSort_(int *a, int *n) {
    int bit = 8;
    int k = (32 + bit - 1) / bit;
    int M = 1 << bit;
    int sz = n - a;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;

        for (int *j = a; j < n; j++)
            c[digit(*j, i, bit, M)]++;

        for (int j = 1; j < M; j++)
            c[j] += c[j - 1];

        for (int *j = n - 1; j >= a; j--)
            b[--c[digit(*j, i, bit, M)]] = *j;

        int cur = 0;
        for (int *j = a; j < n; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);
}

void radixSort(int *a, size_t n) {
    radixSort_(a, a + n);
}


long long getBubbleSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (size_t i = 0; ++nComps && i < n - 1; i++)
        for (size_t j = n - 1; ++nComps && j > i; j--)
            if (++nComps && a[j - 1] > a[j]) {
                swap(&a[j - 1], &a[j]);
            }
    return nComps;
}

long long getSelectionSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (int i = 0; ++nComps && i < n; i++) {
        int min = a[i];
        int minIndex = i;
        for (int j = i + 1; ++nComps && j < n; j++)
            if (++nComps && a[j] < min) {
                min = a[j];
                minIndex = j;
            }
        if (++nComps && i != minIndex)
            swap(&a[i], &a[minIndex]);
    }
    return nComps;
}

long long getInsertionSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (size_t i = 1; ++nComps && i < n; i++) {
        int t = a[i];
        size_t j = i;
        while (++nComps && j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
    return nComps;
}

long long getCombSortNComp(int *a, size_t n) {
    size_t step = n;
    int swapped = 1;
    long long nComps = 0;
    while (++nComps && step > 1 || swapped) {
        if (++nComps && step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; ++nComps && j < n; ++i, ++j)
            if (++nComps && a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
    return nComps;
}

long long getShellSortNComp(int *a, size_t n) {
    long long nComps = 0;
    size_t j;
    int tmp;
    for (size_t step = n / 2; ++nComps && step > 0; step /= 2)
        for (size_t i = step; ++nComps && i < n; i++) {
            tmp = a[i];
            for (j = i; ++nComps && j >= step; j -= step) {
                if (++nComps && tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }
    return nComps;
}

long long getRadixSortNComps_(int *a, int *n) {
    long long nComps = 0;
    int bit = 8;
    int k = (32 + bit - 1) / bit;
    int M = 1 << bit;
    int sz = n - a;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; ++nComps && i < k; i++) {
        for (int j = 0; ++nComps && j < M; j++)
            c[j] = 0;
        for (int *j = a; ++nComps && j < n; j++)
            c[digit(*j, i, bit, M)]++;
        for (int j = 1; ++nComps && j < M; j++)
            c[j] += c[j - 1];
        for (int *j = n - 1; ++nComps && j >= a; j--)
            b[--c[digit(*j, i, bit, M)]] = *j;
        int cur = 0;
        for (int *j = a; ++nComps && j < n; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);
    return nComps;
}

long long getRadixSortNComps(int *a, size_t n) {
    return getRadixSortNComps_(a, a + n);
}
