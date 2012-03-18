#include "memory.h"

size_t create_heap(heap_t * heap_desc, FILE *preload_fp) {
    size_t size = 4096;

    // If we have a heap-file size it up
    if (preload_fp) {
        // Get the size of the code-file
        fseek(preload_fp, 0L, SEEK_END);
        size_t sz = ftell(preload_fp);
        fseek(preload_fp, 0L, SEEK_SET);
        if (sz / sizeof(uint16_t) > 4096) {
            printf("VM Error: Heap-file won't fit in allocated heap!");
            return -1;
        }
        if (sz % sizeof(uint16_t) == 1) {
            printf("VM Error: Heap-file is not aligned to 16-bits!");
            return -2;
        }
        size = sz;
    }

    // Allocate our heap
    (*heap_desc).heap = malloc(sizeof(uint16_t) * size);

    if (!(*heap_desc).heap) {
        printf("VM Error: Cannot allocate heap!");
        return -4;
    }

    (*heap_desc).heap_size = size;

    // If we have a heap-file read it in
    if (preload_fp) {
        if (fread((*heap_desc).heap, sizeof(uint16_t), size, preload_fp) == size) {
            printf("VM Error: Heap-File did not read in properly!");
            free((*heap_desc).heap);
            (*heap_desc).heap = NULL;
            size = 0;
        }
    }

    return size;
}

size_t create_codespace(uint16_t ** code, FILE * fp) {
    size_t sz = 0;
    // Size up our code-space and read in our code
    if (fp) {
        // Get the size of the code-file
        fseek(fp, 0L, SEEK_END);
        sz = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        // Malloc a code space
        *code = malloc(sizeof(char) * sz);
        if (*code == NULL) {
            printf("VM Error: Cannot allocate code memory!");
            return -3;
        }

        // Read in our code file
        if (fread(*code, sizeof(char), sz, fp) != sz) {
            free(*code);
            return -5;
        }
    }

    return sz;
}
