#include <stdio.h>

#include "lett.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    struct lt_chunk chunk;
    lt_chunk_init(&chunk);

    lt_chunk_add(&chunk, LT_OP_HALT);

    struct lt_vm vm;
    lt_vm_init(&vm);

    lt_vm_execute(&vm, &chunk);

    lt_vm_free(&vm);

    lt_chunk_free(&chunk);

    return 0;
}
