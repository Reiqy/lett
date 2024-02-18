#include "lt_chunk.h"

#include "lt_utils.h"

void lt_chunk_init(struct lt_chunk *chunk)
{
    chunk->code = NULL;
    chunk->capacity = 0;
    chunk->count = 0;
}

void lt_chunk_free(struct lt_chunk *chunk)
{
    if (chunk->code != NULL) {
        lt_free(chunk->code);
    }

    lt_chunk_init(chunk);
}

void lt_chunk_add(struct lt_chunk *chunk, uint8_t byte)
{
    if (chunk->capacity <= chunk->count) {
        chunk->capacity = lt_grow(chunk->capacity);
        chunk->code = lt_realloc(chunk->code, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}
