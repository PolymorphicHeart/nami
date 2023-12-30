#ifndef NAMI_MEMORY_H
#define NAMI_MEMORY_H

#include "core.h"

NMAPI void* nm_heap_new (u64 size);
NMAPI void* nm_heap_resize (void* ptr, u64 size);
NMAPI void nm_heap_free (void* ptr);

#endif // NAMI_MEMORY_H