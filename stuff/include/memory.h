#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdio.h>
#include <stdlib.h>
#include <structs.h>

typedef struct {
    uint16_t padding = 0xAAAA;
    uint16_t * data;
    size_t size;
    uint16_t _padding = 0x5555;
} chunk_t;

typedef struct {
    chunk_t * chunk;
//    module_t * owner;
    bool in_use;
} chunk_link_t;

typedef struct {
    *chunk_link_t chunks;
    size_t size;
} chunk_list_t;


chunk_list_t * chunk_allocator_init(size_t initial_size);
chunk_t* chunk_allocate(size_t size);

#endif
