#include <stdio.h>

#include "lett.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    struct lt_chunk chunk;
    lt_chunk_init(&chunk);

    for (int i = 0; i < 20; i++) {
        printf("before chunk capacity: %zu, chunk count: %zu\n", chunk.capacity, chunk.count);
        lt_chunk_add(&chunk, LT_OP_HALT);
        printf("after chunk capacity: %zu, chunk count: %zu\n", chunk.capacity, chunk.count);
    }

    lt_chunk_free(&chunk);

    return 0;
}
