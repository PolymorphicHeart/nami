#include <nami/entry.h>
#include <nami/str.h>
#include "test.h"

i32 nm_main (nm_vec(const c8*) args)
{
    nm_str msg0 = nm_str_new("friends");
    nm_str msg1 = nm_str_fmt(nm_str_lit("hello: {i32} {{not !} and {str}"), -1337, msg0);
    printf("%s\n", msg1.buf);
}
