#include "lt_chunk.h"

void lt_chunk_init(struct lt_chunk *chunk)
{
    lt_array_lt_byte_init(&chunk->code);
}

void lt_chunk_free(struct lt_chunk *chunk)
{
    lt_array_lt_byte_free(&chunk->code);
}

void lt_chunk_add(struct lt_chunk *chunk, lt_byte byte)
{
    lt_array_lt_byte_add(&chunk->code, byte);
}
