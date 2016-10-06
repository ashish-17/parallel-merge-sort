#include "parallelMS.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Privatge data structures

typedef struct thread_data {
    void* data;
    int item_size;
    int l;
    int r;
    int (*comparator)(void*, void*);
    void* aux_memory;
    int num_threads;
} thread_data_t;

// Private functions
static void merge(void* data, int item_size, int l, int m, int r, int (*comparator)(void*, void*), void* aux_memory);
static void mergeSortHelper(void* data, int item_size, int l, int r, int (*comparator)(void*, void*), void* aux_memory, int num_threads);
static inline void* threadRoutine(void* data);

void mergeSortParallel(void* data, int item_size, int n, int (*comparator)(void*, void*), int num_threads) {
    void* aux_memory = malloc(item_size*n);
    mergeSortHelper(data, item_size, 0, n-1, comparator, aux_memory, num_threads);
    free(aux_memory);
    aux_memory = NULL;
}

static void mergeSortHelper(void* data, int item_size, int l, int r, int (*comparator)(void*, void*), void* aux_memory, int num_threads) {
    if (l < r) {
        int m = l + (r-l) / 2;
        if (num_threads > 1) {
            pthread_t thread;
            thread_data_t* d = (thread_data_t*)malloc(sizeof(thread_data_t));
            d->data = data;
            d->item_size = item_size;
            d->l = l;
            d->r = m;
            d->comparator = comparator;
            d->aux_memory = aux_memory;
            d->num_threads = num_threads-2;
            pthread_create(&thread, NULL, threadRoutine, (void*)d);
            mergeSortHelper(data, item_size, m+1, r, comparator, aux_memory, num_threads - 2);
            pthread_join(thread, NULL);
            free(d);
        } else {
            mergeSortHelper(data, item_size, l, m, comparator, aux_memory, num_threads);
            mergeSortHelper(data, item_size, m+1, r, comparator, aux_memory, num_threads);
        }

        merge(data, item_size, l, m, r, comparator, aux_memory);
    }
}

static void merge(void* data, int item_size, int l, int m, int r, int (*comparator)(void*, void*), void* aux_memory) {
    int idxLeftArray = 0, idxRightArray = 0, idxMainArray = l;
    int nLeftArray = (m -l + 1), nRightArray = (r - m);

    memcpy((char*)aux_memory + l*item_size, (char*)data + l*item_size, item_size*nLeftArray);
    memcpy((char*)aux_memory + (m+1)*item_size, (char*)data + (m+1)*item_size, item_size*nRightArray);
    
    char* left = (char*)aux_memory + l*item_size;
    char* right = (char*)aux_memory + (m+1)*item_size;
    while (idxLeftArray < nLeftArray && idxRightArray < nRightArray) {
        if (comparator((void*)(left + idxLeftArray*item_size), ((void*)(right + idxRightArray*item_size)) ) < 0) {
            memcpy(((void*)((char*)data + idxMainArray*item_size)), ((void*)(left + idxLeftArray*item_size)), item_size);
            idxLeftArray++;
        } else {
            memcpy(((void*)((char*)data + idxMainArray*item_size)), ((void*)(right + idxRightArray*item_size)), item_size);
            idxRightArray++;
        }
        idxMainArray++;
    }

    while (idxLeftArray < nLeftArray) {
        memcpy(((void*)((char*)data + idxMainArray*item_size)), ((void*)(left + idxLeftArray*item_size)), item_size);
        idxLeftArray++;
        idxMainArray++;
    }

    while (idxRightArray < nRightArray) {
        memcpy(((void*)((char*)data + idxMainArray*item_size)), ((void*)(right + idxRightArray*item_size)), item_size);
        idxRightArray++;
        idxMainArray++;
    }
}

static inline void* threadRoutine(void* data) {
    thread_data_t* d = (thread_data_t*)data;
    mergeSortHelper(d->data, d->item_size, d->l, d->r,d->comparator, d->aux_memory, d->num_threads);
    
    return NULL;
}
