#include "lt_value.h"

#include <stdio.h>

void lt_value_print(struct lt_value value, enum lt_type type)
{
    switch (type) {
        case LT_TYPE_NUMBER:
            printf("%lf", lt_as_number(value));
            return;
        default:
            fprintf(stderr, "Cannot print value of type %d.", type);
            return;
    }
}

LT_DEFINE_ARRAY(lt_value)
