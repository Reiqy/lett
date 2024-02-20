#ifndef LETT_LT_VM_H
#define LETT_LT_VM_H

#include "lt_chunk.h"

#define LT_VM_STACK_SIZE 256

struct lt_vm_stack {
    struct lt_value stack[LT_VM_STACK_SIZE];
    struct lt_value *top;
};

void lt_vm_stack_reset(struct lt_vm_stack *stack);
void lt_vm_stack_push(struct lt_vm_stack *stack, struct lt_value value);
struct lt_value lt_vm_stack_pop(struct lt_vm_stack *stack);

struct lt_vm {
    struct lt_chunk *chunk;
    uint8_t *ip;
    struct lt_vm_stack stack;
};

void lt_vm_init(struct lt_vm *vm);
void lt_vm_free(struct lt_vm *vm);
void lt_vm_execute(struct lt_vm *vm, struct lt_chunk *chunk);

#endif //LETT_LT_VM_H
