#ifndef LETT_LT_CHUNK_H
#define LETT_LT_CHUNK_H

#include <stdint.h>

enum lt_op_code {
    LT_OP_HALT,
};

struct lt_chunk {
    uint8_t *code;
    size_t capacity;
    size_t count;
};

void lt_chunk_init(struct lt_chunk *chunk);
void lt_chunk_free(struct lt_chunk *chunk);
void lt_chunk_add(struct lt_chunk *chunk, uint8_t byte);

#endif //LETT_LT_CHUNK_H
