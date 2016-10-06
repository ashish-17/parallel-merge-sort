#include "seqMS.h"
#include "parallelMS.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

void test(int n, int numThreads);
void print_array(int* arr, int n);
bool is_sorted(void* data, int item_size, int n, int (*comparator)(void*,void*));

int main(int argc, char** argv) {
    if (argc == 3) {
        int n = atoi(argv[1]);
        if (n != 0) {
            int numThreads = atoi(argv[2]);
            if (numThreads != 0) {
                test(n, numThreads);
                printf("\n");
                return 0;
            }
        }
    }
    printf("\n*** Help Start***");
    printf("\n\nInput::");
    printf("\n1st Argument = Number of operations");
    printf("\n2nd Argument = Number of Threads");
    printf("\nif num of threads = 1 then we use sequential merge sort else we go with parallel merge sort");
    printf("\nExample Usage (Sequential) - ./main 10000 1");
    printf("\nExample Usage (Parallel) - ./main 10000 5");
    printf("\n\nOutput(CSV)::\ndata_size, number_of_threads, time_in_seconds");
    printf("\n\n*** Help End***");
    printf("\n");
    return 0;
}

void test(int n, int numThreads) {
    struct timespec start={0,0}, end={0,0};
    long double timeTaken = 0.0;
    
    int *arr = malloc(sizeof(int) * n);

    // Step 1
#ifdef STATS_VERBOSE
    printf("Start generating %d random numbers", n);
#endif
    clock_gettime(CLOCK_MONOTONIC, &start);

    fillWithRandomNumbers(arr, n);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    timeTaken = ((double)end.tv_sec + 1.0e-9*end.tv_nsec) - ((double)start.tv_sec + 1.0e-9*start.tv_nsec);
#ifdef STATS_VERBOSE
    printf("\nSuccess filling random numbers (%.6Lf seconds)", timeTaken);
#endif

    // Step 2
#ifdef STATS_VERBOSE
    printf("\nStart Merge sort operation");
#endif
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (numThreads == 1) {
#ifdef STATS_VERBOSE
        printf(" (Seqential)");
#endif
        mergeSortSeq(arr, sizeof(int), n, &intComparator);
    } else {
#ifdef STATS_VERBOSE
        printf(" (Parallel)");
#endif
        mergeSortParallel(arr, sizeof(int), n, &intComparator, numThreads);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    timeTaken = ((double)end.tv_sec + 1.0e-9*end.tv_nsec) - ((double)start.tv_sec + 1.0e-9*start.tv_nsec);
#ifdef STATS_VERBOSE
    printf("\nMerge sort completed in %.6Lf seconds", timeTaken);
#else
    printf("%d,%d,%.6Lf", n, numThreads, timeTaken);
#endif

    // Step 3
#ifdef STATS_VERBOSE
    printf("\nStart Verification");
#endif
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    bool sorted = is_sorted(arr, sizeof(int), n, &intComparator);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    timeTaken = ((double)end.tv_sec + 1.0e-9*end.tv_nsec) - ((double)start.tv_sec + 1.0e-9*start.tv_nsec);
    if (sorted) {
#ifdef STATS_VERBOSE
        printf("\nVerification successful (%.6Lf seconds)", timeTaken);
#endif
    } else {
        printf("\nVerification failed (%.6Lf seconds)", timeTaken);
    }
}

void print_array(int* arr, int n) {
    int idx = 0;
    printf("\n");
    for (idx = 0; idx < n; ++idx) {
        printf("%d ", arr[idx]);
    }
}

bool is_sorted(void* data, int item_size, int n, int (*comparator)(void*,void*)) {
    int idx = 0;
    for (idx = 1; idx < n; ++idx) {
        if (comparator((char*)data + item_size*(idx-1), (char*)data + item_size*(idx)) <= 0) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}
