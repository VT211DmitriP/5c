#include "estimationOfComplexityOfAlgorithms.h"

void outputArray_(const int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

bool isOrdered(const int *a, size_t size) {
    for (int i = 0; i < size - 1; i++)
        if (a[i] > a[i + 1])
            return false;

    return true;
}

void checkTime(void (*sortFunc)(int *, size_t),
               void (*generateFunc)(int *, size_t),
               size_t size, char *experimentName) {

    static size_t runCounter = 1;
    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({ sortFunc(innerBuffer, size); }, time);

    // результаты замера
    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);

        // запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
    }
}

void generateRandomArray(int *a, size_t size) {
    srand(time(0));
    for (int i = 0; i < size; i++)
        a[i] = rand() % 10000;
}

void generateOrderedArray(int *a, size_t size) {
    for (int i = 0; i < size; i++) {
        a[i] = i;
    }
}

void generateOrderedBackwards(int *a, size_t size) {
    for (int i = 0; i < size; i++) {
        a[i] = size - i;
    }
}

void timeExperiment() {
    // описание функций сортировки
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {bubbleSort,    "bubbleSort"},
            {combSort,      "combSort"},
            {shellSort,     "ShellSort"},
            {radixSort,     "radixSort"},

    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            // генерируется случайный массив
            {generateRandomArray,      "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray,     "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }
}

void checkCompares(long long int (*sortFunc)(int *, size_t),
                   void (*generateFunc)(int *, size_t),
                   size_t size, char *experimentName) {
    static size_t runCounter = 1;

    int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    long long nComps = sortFunc(innerBuffer, size);

    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Compares: %lld\n", nComps);

        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (NULL == f) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %lld\n", size, nComps);
        fclose(f);
    } else {
        printf("Wrong!\n");

        outputArray_(innerBuffer, size);

        exit(1);
    }
}

void comparesExperiment() {
    // описание функций сортировки
    SortFunc_ sorts[] = {
            {getSelectionSortNComp, "selectionSort"},
            {getInsertionSortNComp, "insertionSort"},
            {getBubbleSortNComp, "bubbleSort"},
            {getCombSortNComp, "combSort"},
            {getShellSortNComp, "shellSort"},
            {getRadixSortNComps, "radixSort"}
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            // генерируется случайный массив
            {generateRandomArray,      "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray,     "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };

    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf("----------------------------\n");
        printf("Size: %d\n", size);

        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                static char filename[128];
                sprintf(filename, "%s_%s_compares",
                        sorts[i].name, generatingFuncs[j].name);
                checkCompares(sorts[i].sort,
                              generatingFuncs[j].generate,
                              size,
                              filename);

            }
        }

        printf("\n");
    }

}