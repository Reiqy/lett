#ifndef LETT_LT_CHUNK_H
#define LETT_LT_CHUNK_H

#include <stdint.h>

#include "lt_collections.h"
#include "lt_value.h"

enum lt_op_code {
    LT_OP_HALT,
};

struct lt_chunk {
    struct lt_array_lt_byte code;
};

void lt_chunk_init(struct lt_chunk *chunk);
void lt_chunk_free(struct lt_chunk *chunk);
void lt_chunk_add(struct lt_chunk *chunk, uint8_t byte);

#endif //LETT_LT_CHUNK_H
