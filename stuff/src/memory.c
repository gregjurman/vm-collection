#include "memory.h"

chunk_t * arena_chunk_malloc(size_t element_size, size_t size);
chunk_t * arena_chunk_malloc(size_t size);
void arena_chunk_free(arena_t * arena, chunk_t * chunk);

arena_t * arena_init(size_t initial_size);
size_t arena_active_chunk_count(arena_t * arena);
size_t arena_wired_chunk_count(arena_t * arena);
size_t arena_unused_chunk_count(arena_t * arena);
void arena_destroy(arena_t * arena);
