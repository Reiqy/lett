#include <stdio.h>

#include "lett.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    struct lt_chunk chunk;
    lt_chunk_init(&chunk);

    lt_chunk_add_const(&chunk, lt_number_value(1.2));
    lt_chunk_add_const(&chunk, lt_number_value(3.4));

    lt_chunk_add(&chunk, LT_OP_ADD);

    lt_chunk_add_const(&chunk, lt_number_value(5.6));

    lt_chunk_add(&chunk, LT_OP_DIVIDE);
    lt_chunk_add(&chunk, LT_OP_NEGATE);

    lt_chunk_add(&chunk, LT_OP_PRINT_NUM);

    lt_chunk_add(&chunk, LT_OP_HALT);

    struct lt_vm vm;
    lt_vm_init(&vm);

    lt_vm_execute(&vm, &chunk);

    lt_vm_free(&vm);

    lt_chunk_free(&chunk);

    return 0;
}
