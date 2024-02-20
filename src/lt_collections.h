#ifndef LETT_LT_COLLECTIONS_H
#define LETT_LT_COLLECTIONS_H

#include <stdint.h>

#include "lt_memory.h"
#include "lt_common.h"

#define LT_DECLARE_ARRAY(type)                                         \
    struct lt_array_##type {                                           \
        type *array;                                                   \
        size_t capacity;                                               \
        size_t count;                                                  \
    };                                                                 \
                                                                       \
void lt_array_##type##_init(struct lt_array_##type *array);            \
void lt_array_##type##_free(struct lt_array_##type *array);            \
void lt_array_##type##_add(struct lt_array_##type *array, type item);

#define LT_DEFINE_ARRAY(type)                                          \
void lt_array_##type##_init(struct lt_array_##type *array)             \
{                                                                      \
    array->array = NULL;                                               \
    array->capacity = 0;                                               \
    array->count = 0;                                                  \
}                                                                      \
                                                                       \
void lt_array_##type##_free(struct lt_array_##type *array)             \
{                                                                      \
    if (array->array != NULL) {                                        \
        lt_free(array->array);                                         \
    }                                                                  \
                                                                       \
    lt_array_##type##_init(array);                                     \
}                                                                      \
                                                                       \
void lt_array_##type##_add(struct lt_array_##type *array, type item) { \
    if (array->capacity <= array->count) {                             \
        array->capacity = lt_grow(array->capacity);                    \
        array->array = lt_realloc(array->array, array->capacity);      \
    }                                                                  \
                                                                       \
    array->array[array->count] = item;                                 \
    array->count++;                                                    \
}

LT_DECLARE_ARRAY(lt_byte)

#endif //LETT_LT_COLLECTIONS_H
