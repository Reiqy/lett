#ifndef LETT_LT_VALUE_H
#define LETT_LT_VALUE_H

#include <stdlib.h>

#include "lt_collections.h"

enum lt_type {
    LT_TYPE_NUMBER,
};

typedef double lt_number;

typedef struct lt_value {
    union {
        lt_number number;
    } as;
} lt_value;

void lt_value_print(struct lt_value value, enum lt_type type);

#define lt_as_number(value) ((value).as.number)

#define lt_number_value(value) ((struct lt_value){ .as.number = (value) })

LT_DECLARE_ARRAY(lt_value)

#endif //LETT_LT_VALUE_H
