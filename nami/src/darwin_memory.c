#include "nami/memory.h"

#if defined(NAMI_PLATFORM_DARWIN)

typedef struct heap_block_t
{
    
} heap_block_t;

void* nm_heap_new (u64 size)
{

}

void* nm_heap_resize (void* ptr, u64 size)
{

}

void nm_heap_free (void* ptr)
{

}

#endif // NAMI_PLATFORM_DARWIN