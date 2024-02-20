#include "lt_chunk.h"

#include <stdio.h>

void lt_chunk_init(struct lt_chunk *chunk)
{
    lt_array_lt_byte_init(&chunk->code);
    lt_array_lt_value_init(&chunk->constants);
}

void lt_chunk_free(struct lt_chunk *chunk)
{
    lt_array_lt_value_free(&chunk->constants);
    lt_array_lt_byte_free(&chunk->code);
}

void lt_chunk_add(struct lt_chunk *chunk, lt_byte byte)
{
    lt_array_lt_byte_add(&chunk->code, byte);
}

static size_t add_const(struct lt_chunk *chunk, struct lt_value value)
{
    lt_array_lt_value_add(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void lt_chunk_add_const(struct lt_chunk *chunk, struct lt_value value)
{
    size_t index = add_const(chunk, value);
    if (index > LT_MAX_CONST_INDEX) {
        fprintf(stderr, "Too many constants in single chunk.\n");
        exit(EXIT_FAILURE);
    }

    lt_chunk_add(chunk, LT_OP_CONST);
    lt_chunk_add(chunk, index);
}
