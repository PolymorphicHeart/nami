#ifndef NAMI_VEC_H
#define NAMI_VEC_H

#include "core.h"
#include "memory.h"

/* ------ Public Vector API ---------------------
 * ----------------------------------------------
*/

// Defines an vector of type T.
#define nm_vec(T) T*

// Creates a new vector for elements of type T.
#define nm_vec_new(T) (T*)_nm_vec_create(sizeof(T), 0)

// Creates a new vector for elements of type T with a reserved count.
#define nm_vec_new_res(T, count) (T*)_nm_vec_create(sizeof(T), count)

// Destroys and cleans up memory allocated by vec.
#define nm_vec_free(vec) free(_nm_vec_get_base(vec)); vec = nm_nptr

// Returns the number of elements in the vec.
#define nm_vec_len(vec) (_nm_vec_get_count(vec))

// Returns the value stored at the given index.
#define nm_vec_at(vec, index) (vec[index])

// Appends the end of the vector with the given value.
#define nm_vec_push_back(vec, val)                    \
{                                                     \
    _nm_vec_ensure_size(vec);                         \
    ((typeof(vec))vec)[_nm_vec_get_count(vec)] = val; \
    _nm_vec_get_count(vec) ++;                        \
}

// Removes the last element of the vector.
#define nm_vec_pop_back(vec)                                   \
{                                                              \
    if (_nm_vec_get_count(vec) > 0) _nm_vec_get_count(vec) --; \
}

// Removes the first element of the vector.
#define nm_vec_pop_front(vec)                     \
{                                                 \
    if (_nm_vec_get_count(vec) > 1)               \
    {                                             \
        _nm_vec_get_count(vec) --;                \
        memmove                                   \
        (                                         \
            ((c8*)vec),                           \
            ((c8*)vec) + _nm_vec_get_stride(vec), \
            (_nm_vec_get_size(vec))               \
        );                                        \
    }                                             \
    else { nm_vec_pop_back(vec); }                \
}

// Removes the element at the given index.
#define nm_vec_pop_at(vec, index)                                     \
{                                                                     \
    if (_nm_vec_get_count(vec) > index)                               \
    {                                                                 \
        _nm_vec_get_count(vec) --;                                    \
        if (_nm_vec_get_count(vec) > 1)                               \
        {                                                             \
            memmove                                                   \
            (                                                         \
                ((c8*)vec) + (_nm_vec_get_stride(vec) * index),       \
                ((c8*)vec) + (_nm_vec_get_stride(vec) * (index + 1)), \
                _nm_vec_get_size(vec)                                 \
            );                                                        \
        }                                                             \
    }                                                                 \
}

// Collapses the heap capacity to fit the data.
#define nm_vec_resize_to_fit(vec)                                                       \
{                                                                                       \
    if (_nm_vec_get_capacity(vec) > _nm_vec_get_size(vec))                              \
    {                                                                                   \
        _nm_vec_get_capacity(vec) = _nm_vec_get_size(vec);                              \
        vec = (typeof(vec))realloc(_nm_vec_get_base(vec), _nm_vec_get_total_size(vec)); \
        vec = (typeof(vec))((void*)vec + _NM_VEC_HEADER_SIZE);                          \
    }                                                                                   \
}

// Iterates through each element of a vector.
#define nm_vec_foreach(elem, vec, ...)                                            \
{                                                                                 \
    for (u64 elem_vec_iter = 0; elem_vec_iter < nm_vec_len(vec); elem_vec_iter++) \
    {                                                                             \
        elem = vec[elem_vec_iter];                                                \
        { __VA_ARGS__ }                                                           \
    }                                                                             \
}

// Iterates through each element of a vector in reverse.
#define nm_vec_foreach_rev(elem, vec, ...)                                             \
{                                                                                      \
    for (i64 elem_vec_iter = nm_vec_len(vec) - 1; elem_vec_iter > -1; --elem_vec_iter) \
    {                                                                                  \
        elem = vec[elem_vec_iter];                                                     \
        { __VA_ARGS__ }                                                                \
    }                                                                                  \
}

/* ------ Vector Implementation -----------------
 * ----------------------------------------------
*/

#define _NM_VEC_GROWTH_MULT 0x2
#define _NM_VEC_HEADER_SIZE (sizeof(u64) * 0x3)

#define _nm_vec_get_base(ptr)       (((void*)ptr) - _NM_VEC_HEADER_SIZE)
#define _nm_vec_get_stride(ptr)     ((u64*)(((void*)ptr) - _NM_VEC_HEADER_SIZE))[0]
#define _nm_vec_get_count(ptr)      ((u64*)(((void*)ptr) - _NM_VEC_HEADER_SIZE))[1]
#define _nm_vec_get_capacity(ptr)   ((u64*)(((void*)ptr) - _NM_VEC_HEADER_SIZE))[2]
#define _nm_vec_get_size(ptr)       (_nm_vec_get_count(ptr) * _nm_vec_get_stride(ptr))
#define _nm_vec_get_total_size(ptr) (_NM_VEC_HEADER_SIZE + _nm_vec_get_capacity(ptr))

#define _nm_vec_ensure_size(vec)                                                        \
{                                                                                       \
    if ((_nm_vec_get_size(vec) + _nm_vec_get_stride(vec)) > _nm_vec_get_capacity(vec))  \
    {                                                                                   \
        _nm_vec_get_capacity(vec) *= _NM_VEC_GROWTH_MULT;                               \
        vec = (typeof(vec))realloc(_nm_vec_get_base(vec), _nm_vec_get_total_size(vec)); \
        vec = (typeof(vec))((void*)vec + _NM_VEC_HEADER_SIZE);                          \
    }                                                                                   \
}

NM_CPP_HEADER_CHECK_START

static void* _nm_vec_create (u64 stride, u64 count)
{
    u64 capacity = (count > 0) ? stride * count : stride * _NM_VEC_GROWTH_MULT;
    void* ptr = calloc(1, _NM_VEC_HEADER_SIZE + capacity);

    ((u64*)ptr)[0] = stride;
    ((u64*)ptr)[1] = count;
    ((u64*)ptr)[2] = capacity;

    return ptr + _NM_VEC_HEADER_SIZE;
}

NM_CPP_HEADER_CHECK_END

#endif // NAMI_VEC_H
