#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <string.h>

void *reserve_ptr_arr(void *data, size_t element_size, size_t *cap, size_t needed);

#endif