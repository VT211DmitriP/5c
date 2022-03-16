#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "D:\5c_complexityAssessment\sorts\sorts.h"

#ifndef INC_5C_COMPLEXITYASSESSMENT_ESTIMATIONOFCOMPLEXITYOFALGORITHMS_H
#define INC_5C_COMPLEXITYASSESSMENT_ESTIMATIONOFCOMPLEXITYOFALGORITHMS_H

#define TIME_TEST(testCode, time) { \
    clock_t start_time = clock() ; \
    testCode \
        clock_t end_time = clock() ;\
    clock_t sort_time = end_time - start_time ; \
    time = (double) sort_time / CLOCKS_PER_SEC ; \
}

#define ARRAY_SIZE(a) sizeof(a) / sizeof (a[0])

// функция сортировки
typedef struct SortFunc {
    void (*sort )(int *a, size_t n); // указатель на функцию
    // сортировки
    char name[64]; // имя сортировки,
    // используемое при выводе
} SortFunc;

// функция генерации
typedef struct GeneratingFunc {
    void (*generate )(int *a, size_t n); // указатель на функцию
    // генерации последоват.
    char name[64]; // имя генератора,
    // используемое при выводе
} GeneratingFunc;

typedef struct SortFunc_ {
    long long (*sort )(int *a, size_t n); // указатель на функцию сортировки
    char name[64]; // имя сортировки, используемое при выводе
} SortFunc_;

void outputArray_(const int *const a, const size_t n);

bool isOrdered(const int *a, size_t size);

void checkTime(void (*sortFunc )(int *, size_t),
               void (*generateFunc )(int *, size_t),
               size_t size, char *experimentName);

void generateRandomArray(int *a, size_t size);

void generateOrderedArray(int *a, size_t size);

void generateOrderedBackwards(int *a, size_t size);

void timeExperiment();

void checkCompares(long long int (*sortFunc)(int *, size_t),
                   void (*generateFunc)(int *, size_t),
                   size_t size, char *experimentName);

void comparesExperiment();

#endif
