#ifndef NAMI_MEMORY_H
#define NAMI_MEMORY_H

//TODO: implement smart pointers with destructors

#include "core.h"

#define nm_uptr_t(T) __attribute__((cleanup(_nm_mem_free_stack))) T

__attribute__ ((always_inline))
inline static void _nm_mem_free_stack(void* ptr) {
    printf("destructor called!\n");
}


#endif // NAMI_MEMORY_H