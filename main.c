#include "D:\5c_complexityAssessment\estimationOfComplexityOfAlgorithms\estimationOfComplexityOfAlgorithms.h"


double getTime() {
    clock_t start_time = clock();
    int size = 200000;
    int a[size];

    generateRandomArray(a, size);

    insertionSort(a, size);

    clock_t end_time = clock();\
 clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}

int main() {
    //timeExperiment();
    //comparesExperiment();

    printf("%lf", getTime());

    return 0;
}
