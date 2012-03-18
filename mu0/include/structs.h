#include <stdint.h>

#ifndef STRUCTS_H_
#define STRUCTS_H_

// Define how the opcodes look in bit-fields
typedef struct {
    uint16_t s : 12;
    uint16_t opcode : 4;
} operation_struct;

// Our heap definition
typedef struct {
    uint16_t * heap;
    size_t heap_size;
} heap_t;

#endif
