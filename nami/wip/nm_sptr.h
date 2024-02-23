#ifndef NAMI_SPTR_H
#define NAMI_SPTR_H

// NOTE: This nami header is very experimental and may not even exist in the future...

#include "nm_core.h"

NM_CPP_HEADER_CHECK_START

#define nm_make_unique(T, dtor) _nm_uptr_alloc(sizeof(T), dtor)

#define nm_uptr(T) __attribute__((cleanup(_nm_mem_free_stack))) T

struct _nm_uptr_meta
{
    void (*dtor)(void *);
    void* ptr;
};

static struct _nm_uptr_meta* _nm_uptr_get_meta(void* ptr) 
{
    return ptr - sizeof(struct _nm_uptr_meta);
}

__attribute__((malloc))
static void* _nm_uptr_alloc (usize size, void (*dtor)(void *)) 
{
    struct _nm_uptr_meta* meta = malloc(sizeof(struct _nm_uptr_meta) + size);
    *meta = (struct _nm_uptr_meta) {
        .dtor = dtor,
        .ptr  = meta + 1
    };

    //printf("meta: %p ptr: %p\n", meta, meta->ptr);
    return meta->ptr;
}

__attribute__((malloc))
static void* _nm_uptr_realloc (void* ptr, usize size)
{
    void* dtor = _nm_uptr_get_meta(ptr)->dtor;

    struct _nm_uptr_meta* meta = realloc(_nm_uptr_get_meta(ptr), sizeof(struct _nm_uptr_meta) + size);
    *meta = (struct _nm_uptr_meta) {
        .dtor = dtor,
        .ptr  = meta + 1
    };

    //printf("meta: %p ptr: %p\n", meta, meta->ptr);
    return meta->ptr;
}

static void _nm_uptr_free (void* ptr) 
{
    if (ptr == nm_nptr) return;
    struct _nm_uptr_meta* meta = _nm_uptr_get_meta(ptr);
    if (meta->dtor) meta->dtor(ptr);
    free(meta);
}

__attribute__((always_inline))
inline static void _nm_mem_free_stack (void* ptr) 
{
    _nm_uptr_free(*(void **) ptr);
}

NM_CPP_HEADER_CHECK_END

#endif // NAMI_SPTR_H