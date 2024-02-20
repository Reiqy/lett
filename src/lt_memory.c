#include "lt_memory.h"

#include <assert.h>
#include <stdio.h>

void *lt_reallocate(void *ptr, size_t new_size)
{
    if (new_size == 0) {
        assert(ptr != NULL);
        free(ptr);
        return NULL;
    }

    void *result = realloc(ptr, new_size);
    if (result == NULL) {
        fprintf(stderr, "Not enough memory.\n");
        exit(EXIT_FAILURE);
    }

    return result;
}
