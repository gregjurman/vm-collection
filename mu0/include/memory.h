#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdio.h>
#include <stdlib.h>
#include <structs.h>

#define HEAP_CHECK(s) \
    if (s > heap.heap_size) goto TARGET_HEAP_BLOWOUT; 

size_t create_heap(heap_t * heap_desc, FILE *preload_fp);
size_t create_codespace(uint16_t ** code, FILE * fp);

#endif
