#ifndef NAMI_MEMORY_H
#define NAMI_MEMORY_H

//TODO: implement smart pointers with destructors

#include "core.h"

NM_CPP_HEADER_CHECK_START

#define nm_uptr_t(T) __attribute__((cleanup(_nm_mem_free_stack))) T

struct _nm_uptr_meta
{
    void (*destructor)(void *);
    void *ptr;
};

static struct _nm_uptr_meta* _nm_uptr_get_meta(void *ptr) 
{
    return ptr - sizeof (struct _nm_uptr_meta);
}

__attribute__((malloc))
static void* _nm_uptr_alloc(size_t size, void (*destructor)(void *)) 
{
    struct _nm_uptr_meta *meta = calloc(1, sizeof (struct _nm_uptr_meta) + size);
    *meta = (struct _nm_uptr_meta) 
    {
        .destructor = destructor,
        .ptr  = meta + 1
    };
    return meta->ptr;
}

static void _nm_uptr_free(void *ptr) 
{
    if (ptr == nm_nptr_t) return;
    struct _nm_uptr_meta *meta = _nm_uptr_get_meta(ptr);
    //assert(ptr == meta->ptr);
    meta->destructor(ptr);
    free(meta);
}

__attribute__((always_inline))
inline static void _nm_mem_free_stack(void* ptr) 
{
    _nm_uptr_free(*(void **) ptr);
}

NM_CPP_HEADER_CHECK_END

#endif // NAMI_MEMORY_H