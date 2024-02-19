#ifndef LETT_LT_VALUE_H
#define LETT_LT_VALUE_H

enum lt_type {
    LT_TYPE_NUMBER,
};

typedef double lt_number;

struct lt_value {
    union {
        lt_number number;
    } as;
};

void lt_value_print(struct lt_value value, enum lt_type type);

#endif //LETT_LT_VALUE_H
