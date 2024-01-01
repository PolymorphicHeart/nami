#ifndef NM_ARRAY_H
#define NM_ARRAY_H

#include "core.h"

/* -------- Public Array API --------------------
 * ----------------------------------------------
*/

// Creates a new array for elements of type T.
#define nm_array_create(T) (T*)_nm_array_create(sizeof(T), 0)

// Creates a new array for elements of type T with a reserved count.
#define nm_array_create_reserved(T, size) (T*)_nm_array_create(sizeof(T), size)

// Destroys and cleans up memory allocated by array.
#define nm_array_dispose(arr) free(_nm_array_get_base(arr)); arr = nullptr_t

// Returns the number of elements in the array.
#define nm_array_count(arr) (_nm_array_get_count(arr))

// Returns the value stored at the given index.
#define nm_array_at(arr, index) (arr[index])

// Appends the end of the array with the given value.
#define nm_array_push_back(arr, val)                    \
{                                                       \
    _nm_array_ensure_size(arr);                         \
    ((typeof(arr))arr)[_nm_array_get_count(arr)] = val; \
    _nm_array_get_count(arr) ++;                        \
}

// Removes the last element of the array.
#define nm_array_pop_back(arr)                                     \
{                                                                  \
    if (_nm_array_get_count(arr) > 0) _nm_array_get_count(arr) --; \
}

// Removes the first element of the array.
#define nm_array_pop_front(arr)                     \
{                                                   \
    if (_nm_array_get_count(arr) > 1)               \
    {                                               \
        _nm_array_get_count(arr) --;                \
        memmove                                     \
        (                                           \
            ((c8*)arr),                             \
            ((c8*)arr) + _nm_array_get_stride(arr), \
            (_nm_array_get_size(arr))               \
        );                                          \
    }                                               \
    else { nm_array_pop_back(arr); }                \
}

// Removes the element at the given index.
#define nm_array_pop_at(arr, index)                                     \
{                                                                       \
    if (_nm_array_get_count(arr) > index)                               \
    {                                                                   \
        _nm_array_get_count(arr) --;                                    \
        if (_nm_array_get_count(arr) > 1)                               \
        {                                                               \
            memmove                                                     \
            (                                                           \
                ((c8*)arr) + (_nm_array_get_stride(arr) * index),       \
                ((c8*)arr) + (_nm_array_get_stride(arr) * (index + 1)), \
                _nm_array_get_size(arr)                                 \
            );                                                          \
        }                                                               \
    }                                                                   \
}

/* -------- Array Implementation ----------------
 * ----------------------------------------------
*/

#define _NM_ARRAY_GROWTH_MULT 0x2
#define _NM_ARRAY_HEADER_SIZE (sizeof(u64) * 0x3)

#define _nm_array_get_base(ptr)       (((void*)ptr) - _NM_ARRAY_HEADER_SIZE)
#define _nm_array_get_stride(ptr)     ((u64*)(((void*)ptr) - _NM_ARRAY_HEADER_SIZE))[0]
#define _nm_array_get_count(ptr)      ((u64*)(((void*)ptr) - _NM_ARRAY_HEADER_SIZE))[1]
#define _nm_array_get_capacity(ptr)   ((u64*)(((void*)ptr) - _NM_ARRAY_HEADER_SIZE))[2]
#define _nm_array_get_size(ptr)       (_nm_array_get_count(ptr) * _nm_array_get_stride(ptr))
#define _nm_array_get_total_size(ptr) (_NM_ARRAY_HEADER_SIZE + _nm_array_get_capacity(ptr))

#define _nm_array_ensure_size(arr)                                                           \
{                                                                                            \
    if ((_nm_array_get_size(arr) + _nm_array_get_stride(arr)) > _nm_array_get_capacity(arr)) \
    {                                                                                        \
        _nm_array_get_capacity(arr) *= _NM_ARRAY_GROWTH_MULT;                                \
        arr = (typeof(arr))realloc(_nm_array_get_base(arr), _nm_array_get_total_size(arr));  \
        arr = (typeof(arr))((void*)arr + _NM_ARRAY_HEADER_SIZE);                             \
    }                                                                                        \
}

static void* _nm_array_create (u64 stride, u64 count)
{
    u64 capacity = (count > 0) ? stride * count : stride * _NM_ARRAY_GROWTH_MULT;
    void* ptr = calloc(1, _NM_ARRAY_HEADER_SIZE + capacity);

    ((u64*)ptr)[0] = stride;
    ((u64*)ptr)[1] = count;
    ((u64*)ptr)[2] = capacity;

    return ptr + _NM_ARRAY_HEADER_SIZE;
}

#endif // NM_ARRAY_H