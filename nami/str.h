#ifndef NAMI_STR_H
#define NAMI_STR_H

#include "core.h"
#include <stdarg.h>
#include <stdio.h>

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

static nm_str nm_str_lit_size (c8* cstr, usize size)
{
    if (!cstr) return nm_str_empty;

    return (nm_str)
    {
        .buf = cstr,
        .len = size
    };
}

static bool nm_str_eq (nm_str str1, nm_str str2)
{
    if (str1.len != str2.len) return false;

    for (usize i = 0; i < str1.len; i++)
    {
        if (str1.buf[i] != str2.buf[i]) return false;
    }

    return true;
}

/* ------ String Implementation -----------------
 * ----------------------------------------------
*/

static nm_str _nm_str_new (const c8* cstr)
{
    if (!cstr) return nm_str_empty;
    usize len = strlen(cstr);

    nm_str str = 
    {
        .len = len,
        .buf = calloc(1, (len + 1) * sizeof(c8*))
    };

    memmove(str.buf, cstr, len);
    str.buf[str.len] = 0;
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
        .buf = realloc(str1.buf, len + 1)
    };

    memmove(nstr.buf + str1.len, str2.buf, str2.len);
    nstr.buf[nstr.len] = 0;
    return nstr;
}

static nm_str _nm_str_move (nm_str* str)
{
    nm_str nstr = *str;
    *str = nm_str_empty;
    return nstr;
}

static nm_str nm_str_fmt (const nm_str fmt, ...)
{
    nm_str nstr = nm_str_new("");
    nm_str plain = nm_str_new("");
    nm_str tok = nm_str_empty;
    bool tok_look = false;
    va_list va;

    plain.buf = fmt.buf;
    plain.len = 0;

    va_start(va, fmt);

    for (usize i = 0; i < fmt.len; i++)
    {
        if (fmt.buf[i] == '{') 
        {
            nm_str_cat(nstr, plain);
            tok.buf = fmt.buf + (i + 1);
            tok.len = 0;

            if (fmt.buf[i + 1] == '{')
            {
                i++;
                plain.buf = fmt.buf + i;
                plain.len = 1;
                continue;
            }

            tok_look = true;
        }

        else if (tok_look && fmt.buf[i] != '}')
        {
            tok.len ++;
        }

        else if (tok_look && fmt.buf[i] == '}')
        {
            c8 val_buf[1024] = {0};

            if (nm_str_eq(nm_str_lit("f32"), tok))
            {
                snprintf(val_buf, sizeof(val_buf), "%f", va_arg(va, f64));
                nm_str_cat(nstr, nm_str_lit(val_buf));
            }

            else if (nm_str_eq(nm_str_lit("f64"), tok))
            {
                snprintf(val_buf, sizeof(val_buf), "%f", va_arg(va, f64));
                nm_str_cat(nstr, nm_str_lit(val_buf));
            }

            else if (nm_str_eq(nm_str_lit("u32"), tok))
            {
                snprintf(val_buf, sizeof(val_buf), "%u", va_arg(va, u32));
                nm_str_cat(nstr, nm_str_lit(val_buf));
            }

            else if (nm_str_eq(nm_str_lit("u64"), tok))
            {
                snprintf(val_buf, sizeof(val_buf), "%llu", va_arg(va, u64));
                nm_str_cat(nstr, nm_str_lit(val_buf));
            }

            else if (nm_str_eq(nm_str_lit("i32"), tok))
            {
                snprintf(val_buf, sizeof(val_buf), "%i", va_arg(va, i32));
                nm_str_cat(nstr, nm_str_lit(val_buf));
            }

            else if (nm_str_eq(nm_str_lit("i64"), tok))
            {
                snprintf(val_buf, sizeof(val_buf), "%lli", va_arg(va, i64));
                nm_str_cat(nstr, nm_str_lit(val_buf));
            }

            else if (nm_str_eq(nm_str_lit("cstr"), tok))
            {
                nm_str_cat(nstr, nm_str_lit(va_arg(va, c8*)));
            }

            else if (nm_str_eq(nm_str_lit("str"), tok))
            {
                nm_str_cat(nstr, va_arg(va, nm_str));
            }

            tok_look = false;
            plain.buf = fmt.buf + (i + 1);
            plain.len = 0;
        }

        else
        {
            plain.len ++;
        }
    }

    nm_str_cat(nstr, plain);
    va_end(va);

    nstr.buf[nstr.len] = 0;
    return nstr;
}

NM_CPP_HEADER_CHECK_END

#endif // NAMI_STR_H