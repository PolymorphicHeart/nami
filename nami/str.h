#ifndef NAMI_STR_H
#define NAMI_STR_H

#include "core.h"

NM_CPP_HEADER_CHECK_START

/* ------ Public String API ---------------------
 * ----------------------------------------------
*/

typedef struct nm_str
{
    usize len;
    c8* buf;
} nm_str;

#define nm_str_empty (nm_str){0, nm_nptr}

#define nm_str_new(cstr) _nm_str_new(cstr)
#define nm_str_free(str) _nm_str_free(&str)
#define nm_str_move(str) _nm_str_move(&str)

#define nm_str_cat(str1, str2) str1 = _nm_str_cat(str1, str2)

static nm_str nm_str_lit (c8* cstr)
{
    if (!cstr) return nm_str_empty;

    return (nm_str)
    {
        .buf = cstr,
        .len = strlen(cstr)
    };
}

/* ------ String Implementation -----------------
 * ----------------------------------------------
*/

static nm_str _nm_str_new (const c8* cstr)
{
    if (!cstr) return nm_str_empty;
    usize len = strlen(cstr);
    if (len < 1) return nm_str_empty;

    nm_str str = 
    {
        .len = len,
        .buf = calloc(1, len * sizeof(c8*))
    };

    memmove(str.buf, cstr, len);
    return str;
}

static void _nm_str_free (nm_str* str)
{
    if (!str) return;
    free(str->buf);
    *str = nm_str_empty;
}

static nm_str _nm_str_cat (nm_str str1, nm_str str2)
{
    if (!str1.buf) return nm_str_empty;
    if (!str2.buf) return str1;
    if (str2.len < 1) return str1;

    usize len = str1.len + str2.len;

    nm_str nstr =
    {
        .len = len,
        .buf = realloc(str1.buf, len)
    };

    memmove(nstr.buf + str1.len, str2.buf, str2.len);
    return nstr;
}

static nm_str _nm_str_move (nm_str* str)
{
    nm_str nstr = *str;
    *str = nm_str_empty;
    return nstr;
}

NM_CPP_HEADER_CHECK_END

#endif // NAMI_STR_H