#ifndef NAMI_STRING_H
#define NAMI_STRING_H

#include "core.h"

/* ------ Public String API ---------------------
 * ----------------------------------------------
*/

#define NM_STR   ((u8)0)
#define NM_STR_C ((i8)0)

// Creates a new string from a const string.
#define nm_str_create(cstr) _nm_str_create(cstr)

// Destroys and cleans up memory allocated by the string.
#define nm_str_dispose(str) free(_nm_str_get_base(str)); str = nm_nptr_t

// Returns the size of the string in bytes, excluding the null-terminator.
#define nm_str_size(str) (_nm_str_get_capacity(str) - 1)

// Append a c-style or dynamic string to the current one.
#define nm_str_append(T, str1, str2) _Generic((T),  \
    u8: str1 = _nm_str_append_str(str1, str2),      \
    i8: str1 = _nm_str_append_cstr(str1, str2),     \
    default: str1 = _nm_str_append_cstr(str1, str2))

/* ------ String Implementation -----------------
 * ----------------------------------------------
*/

#define _NM_STRING_HEADER_SIZE (sizeof(u64) * 0x1)

#define _nm_str_get_base(ptr)       (ptr - _NM_STRING_HEADER_SIZE)
#define _nm_str_get_capacity(ptr)   ((u64*)(ptr - _NM_STRING_HEADER_SIZE))[0]
#define _nm_str_get_total_size(ptr) (_NM_STRING_HEADER_SIZE + _nm_str_get_capacity(ptr))
#define _nm_str_seek_end(ptr)       ((ptr + _nm_str_get_capacity(ptr)) - 1)

static c8* _nm_str_ensure_size (c8* str, u64 size)
{
    _nm_str_get_capacity(str) += size;

    str = realloc(_nm_str_get_base(str), _nm_str_get_total_size(str));
    str += _NM_STRING_HEADER_SIZE;

    return str;
}

static c8* _nm_str_append_str (c8* str1, const c8* str2)
{
    if (!str2) return str1;
    else if (!str1) return nm_nptr_t;

    u64 str2_len = _nm_str_get_capacity(str2);

    if (str2_len < 1) return str1;

    str1 = _nm_str_ensure_size(str1, str2_len);
    c8* iter = _nm_str_seek_end(str1);

    memmove(iter - str2_len, str2, str2_len);
    iter[0] = '\0';

    return str1;
}

static c8* _nm_str_append_cstr (c8* str, const c8* cstr)
{
    if (!cstr) return str;
    else if (!str) return nm_nptr_t;

    u64 cstr_len = strlen(cstr);
    if (cstr_len < 1) return str;

    str = _nm_str_ensure_size(str, cstr_len);
    c8* iter = _nm_str_seek_end(str);

    memmove(iter - cstr_len, cstr, cstr_len);
    iter[0] = '\0';

    return str;
}

static c8* _nm_str_create (const c8* cstr)
{
    if (!cstr) cstr = "";

    u64 capacity = strlen(cstr) + 1;
    c8* ptr = calloc(1, _NM_STRING_HEADER_SIZE + capacity);

    ((u64*)ptr)[0] = capacity;

    ptr += _NM_STRING_HEADER_SIZE;

    if (capacity > 1) memmove(ptr, cstr, capacity);
    return ptr;
}

#endif // NAMI_STRING_H