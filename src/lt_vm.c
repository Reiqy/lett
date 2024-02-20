#include "lt_vm.h"

#include <stdio.h>

void lt_vm_init(struct lt_vm *vm)
{
    (void)vm;
}

void lt_vm_free(struct lt_vm *vm)
{
    (void)vm;
}

static void vm_loop(struct lt_vm *vm);

void lt_vm_execute(struct lt_vm *vm, struct lt_chunk *chunk)
{
    vm->chunk = chunk;
    vm->ip = chunk->code.array;
    vm_loop(vm);
}

static void vm_loop(struct lt_vm *vm)
{
#define read_byte() (*vm->ip)

    for (;;) {
        switch (read_byte()) {
            case LT_OP_HALT:
                printf("Execution finished.\n");
                return;
        }
    }
}
