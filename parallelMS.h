#ifndef PARALLELMS_H
#define PARALLELMS_H

void mergeSortParallel(void* data, int item_size, int n, int (*comparator)(void*, void*), int numThreads);

#endif
