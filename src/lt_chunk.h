#ifndef LETT_LT_CHUNK_H
#define LETT_LT_CHUNK_H

#include <stdint.h>

#include "lt_collections.h"
#include "lt_value.h"

#define LT_MAX_CONST_INDEX UINT8_MAX

enum lt_op_code {
    LT_OP_HALT,
    LT_OP_PRINT_NUM,
    LT_OP_CONST,
    LT_OP_NEGATE,
    LT_OP_ADD,
    LT_OP_SUBTRACT,
    LT_OP_MULTIPLICATE,
    LT_OP_DIVIDE,
};

struct lt_chunk {
    struct lt_array_lt_byte code;
    struct lt_array_lt_value constants;
};

void lt_chunk_init(struct lt_chunk *chunk);
void lt_chunk_free(struct lt_chunk *chunk);
void lt_chunk_add(struct lt_chunk *chunk, uint8_t byte);
void lt_chunk_add_const(struct lt_chunk *chunk, struct lt_value value);

#endif //LETT_LT_CHUNK_H
