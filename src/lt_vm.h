#ifndef LETT_LT_VM_H
#define LETT_LT_VM_H

#include "lt_chunk.h"

struct lt_vm {
    struct lt_chunk *chunk;
    uint8_t *ip;
};

void lt_vm_init(struct lt_vm *vm);
void lt_vm_free(struct lt_vm *vm);
void lt_vm_execute(struct lt_vm *vm, struct lt_chunk *chunk);

#endif //LETT_LT_VM_H
