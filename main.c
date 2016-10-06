#include "seqMS.h"
#include "parallelMS.h"
#include "utils.h"
#include <stdio.h>
#include <sys/time.h>

void print_array(int* arr, int n);
int main(int argc, char** argv) {
    time_t t;
    srand((unsigned)&t);
    int n = 500000000;
    int *arr = malloc(sizeof(int) * n);
    fillWithRandomNumbers(arr, n);
    //print_array(arr, n);

    struct timeval start, end;
    gettimeofday(&start, NULL);
    mergeSortParallel(arr, sizeof(int), n, &intComparator, 10);
    //mergeSortSeq(arr, sizeof(int), n, &intComparator);
    gettimeofday(&end, NULL);
    long double timeTaken = ((end.tv_sec + end.tv_usec / 1000000.0) - (start.tv_sec + start.tv_usec / 1000000.0));
    //print_array(arr, n);
    printf("\nTime taken = %.6Lf", timeTaken);
    return 0;
}

void print_array(int* arr, int n) {
    int idx = 0;
    printf("\n");
    for (idx = 0; idx < n; ++idx) {
        printf("%d ", arr[idx]);
    }
}
