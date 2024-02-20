#include "lt_vm.h"

#include <stdio.h>

void lt_vm_stack_reset(struct lt_vm_stack *stack)
{
    stack->top = stack->stack;
}

void lt_vm_stack_push(struct lt_vm_stack *stack, struct lt_value value)
{
    *stack->top = value;
    stack->top++;
}

struct lt_value lt_vm_stack_pop(struct lt_vm_stack *stack)
{
    stack->top--;
    return *stack->top;
}

void lt_vm_init(struct lt_vm *vm)
{
    lt_vm_stack_reset(&vm->stack);
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
#define read_byte() (*vm->ip++)
#define read_const() (vm->chunk->constants.array[read_byte()])

#define push(value) lt_vm_stack_push(&vm->stack, (value))
#define pop() lt_vm_stack_pop(&vm->stack)

    for (;;) {
        switch (read_byte()) {
            case LT_OP_HALT:
                printf("Execution finished.\n");
                return;
            case LT_OP_PRINT_NUM: {
                struct lt_value value = pop();
                lt_value_print(value, LT_TYPE_NUMBER);
                printf("\n");
                break;
            }
            case LT_OP_CONST: {
                struct lt_value constant = read_const();
                push(constant);
                break;
            }
            case LT_OP_NEGATE:
                push(lt_number_value(-lt_as_number(pop())));
                break;
            case LT_OP_ADD: {
                lt_number b = lt_as_number(pop());
                lt_number a = lt_as_number(pop());
                push(lt_number_value(a + b));
                break;
            }
            case LT_OP_SUBTRACT: {
                lt_number b = lt_as_number(pop());
                lt_number a = lt_as_number(pop());
                push(lt_number_value(a - b));
                break;
            }
            case LT_OP_MULTIPLICATE: {
                lt_number b = lt_as_number(pop());
                lt_number a = lt_as_number(pop());
                push(lt_number_value(a * b));
                break;
            }
            case LT_OP_DIVIDE: {
                // TODO: Handle division by zero.
                lt_number b = lt_as_number(pop());
                lt_number a = lt_as_number(pop());
                push(lt_number_value(a / b));
                break;
            }
        }
    }

#undef pop
#undef push

#undef read_const
#undef read_byte
}
