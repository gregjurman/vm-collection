#include <cmath.h>
#include "memory.h"

chunk_list_t* allocator_init(size_t initial_size) {

    // Initialize our container
    chunk_list_t * chunk_list = (chunk_list_t*) malloc(sizeof(chunk_list_t));

    if (chunk_list) {
        // Allocate our initial chunk list
        chunk_list.chunks = (chunk_link_t*) malloc(sizeof(chunk_link_t) * inital_size);
        if (chunk_list.chunks) {
            chunk_list.size = initial_size; 
        } else {
            free(chunk_list);
            chunk_list = NULL;
        }
    }

    return chunk_list;
}

size_t allocator_resize(chunk_list_t *c_list, size_t additional) {
    size_t new_size = (*c_list).size;

    if (c_list) {
        // Allocate our initial chunk list
        (chunk_link_t*) new_list = (chunk_link_t*) realloc((*c_list).chunks, 
            sizeof(chunk_link_t) * ((*c_list).size + additional));

        if (new_list) {
            (*c_list).chunks = new_list;
            new_size += additional;
            (*c_list).size += additional;
        } else {
            new_size = 0; // There was an error allocating
        }
    }

    return new_size;
}

size_t allocator_active_chunk_count(chunk_list_t *c_list) {
    size_t total = (*c_list).size;
    size_t active = 0;

    chunk_link_t * chunks = (*c_list).chunks;

    for (size_t i = 0; i < total; i++) {
        if (chunks[i]) {
            if (chunks[i].chunk && chunks[i].in_use) {
                active++;
            }
        }
    }
    
    return active;           
}

size_t allocator_wired_chunk_count(chunk_list_t *c_list) {
    size_t total = (*c_list).size;
    size_t wired = 0;

    chunk_link_t * chunks = (*c_list).chunks;

    for (size_t i = 0; i < total; i++) {
        if (chunks[i]) {
            if (chunks[i].chunk) {
                wired++;
            }
        }
    }

    return wired;
}

size_t allocator_unused_chunk_count(chunk_list_t *c_list) {
    size_t total = (*c_list).size;
    size_t unused = 0;

    chunk_link_t * chunks = (*c_list).chunks;

    for (size_t i = 0; i < total; i++) {
        if (chunks[i]) {
            if (chunks[i].chunk && !chunks[i].in_use) {
                unused++;
            }
        }
    }

    return unused;
}

chunk_link_t* allocator_get_unused_sized_chunks(chunk_link_t * unused_chunks, chunk_list_t *c_list, size_t needed_size) {
    chunk_link_t * chunks = (*c_list).chunks;
    unused_chunks = malloc(sizeof(chunk_link_t) * (*c_list).size);

    size_t j = 0;

    for (size_t i = 0; i < total; i++) {
        if (chunks[i]) {
            if (chunks[i].chunk && !chunks[i].in_use && chunks[i].chunk.size >= needed_size) {
                unused_chunks[j] = chunks[i];
                j++;
            }
        }
    }

    return j;
}

chunk_link_t * allocator_get_unused_chunk(chunk_list_t *c_list, size_t chunk_size) {
    chunk_link_t * good_match = NULL;
    chunk_link_t * unused_chunks;
    size_t num_unused = allocator_get_unused_sized_chunks(unused_chunks, c_list, chunk_size);

    if (num_unused > 0) {
        int req_exp = 0;
        frexp(chunk_size, &req_exp);

        size_t good_fit = chunk_size;
        for (int i = 0; i < num_unused; i++) {
            int exp = 0;
            frexp(unused_chunks[i].size, &exp);
            if (exp > req_exp && exp-1 <= req_exp) {
                // if exp is bigger than the requested, but not 2 bigger than the req
                good_match = unused_chunks[i];
            }
        }
        if (!good_match) {
            // screw it use the first one
            good_match = unused_chunks[0];
        }
    }

    return good_match
}

size_t allocator_create_chunk(chunk_t * chunk, chunk_list_t *c_list, size_t chunk_size) {
    chunk_link_t * old_chunk = allocator_get_unused_chunk(c_list, chunk_size);

    if (old_chunk) {
        (*old_chunk).in_use = true;
        chunk = old_chunk.chunk;
        return (*chunk).size;
    } else {
        // TODO: Allocate a new chunk from the chunk list

    }

}
