#include "seqMS.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Private functions
void merge(void* data, int item_size, int l, int m, int r, int (*comparator)(void*, void*), void* aux_memory);
void mergeSortHelper(void* data, int item_size, int l, int r, int (*comparator)(void*, void*), void* aux_memory);

void mergeSortSeq(void* data, int item_size, int n, int (*comparator)(void*, void*)) {
    void* aux_memory = malloc(item_size*n);
    mergeSortHelper(data, item_size, 0, n-1, comparator, aux_memory);
    free(aux_memory);
    aux_memory = NULL;
}

void mergeSortHelper(void* data, int item_size, int l, int r, int (*comparator)(void*, void*), void* aux_memory) {
    if (l < r) {
        int m = l + (r-l) / 2;
        mergeSortHelper(data, item_size, l, m, comparator, aux_memory);
        mergeSortHelper(data, item_size, m+1, r, comparator, aux_memory);

        merge(data, item_size, l, m, r, comparator, aux_memory);
    }
}

void merge(void* data, int item_size, int l, int m, int r, int (*comparator)(void*, void*), void* aux_memory) {
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
