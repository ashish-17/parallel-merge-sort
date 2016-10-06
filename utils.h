#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

static inline int intComparator(void* a, void* b) {
    return (*(int*)a - *(int*)b);
}

static inline int charComparator(void* a, void* b) {
    return (*(char*)a - *(char*)b);
}

static inline void fillWithRandomNumbers(int* memory, int n) {
    int idx = 0;
    for (idx = 0; idx < n; ++idx) {
        memory[idx] = (rand() % n);
    }
}

#endif
