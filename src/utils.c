#include "utils.h"

#include <stdlib.h>
#include <string.h>

void *reserve_ptr_arr(void *data, size_t element_size, 
                      size_t *cap, size_t needed)
{
	if (cap == NULL || element_size == 0)
        return NULL;

    if (*cap >= needed) 
        return data;
    
    size_t new_cap = *cap ? *cap : 4;
    
    while (new_cap < needed)
        new_cap <<= 1;
    
    
    void *tmp_ptr = realloc(data, new_cap * element_size);;

    if (tmp_ptr == NULL) 
        return NULL;
    
    *cap = new_cap;
    
    return tmp_ptr;
}