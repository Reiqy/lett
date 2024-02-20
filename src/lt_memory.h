#ifndef LETT_LT_MEMORY_H
#define LETT_LT_MEMORY_H

#include <stdlib.h>

void *lt_reallocate(void *ptr, size_t new_size);

#define lt_grow(size) ((size) < 8 ? 8 : 2 * (size))
#define lt_free(ptr) lt_reallocate((ptr), 0)
#define lt_realloc(ptr, new_size) lt_reallocate((ptr), sizeof *(ptr) * (new_size))

#endif //LETT_LT_MEMORY_H
