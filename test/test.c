#include <nami/entry.h>
#include <nami/containers/string.h>

#include <stdio.h>
#include "test.h"

i32 nm_main (const c8** args)
{
    c8* str = nm_str_create("args [");
    c8* str2 = nm_str_create(" ]");

    for (u64 i = 0; i < nm_array_count(args); i++) 
    {
        nm_str_append(NM_STR_C, str, " ");
        nm_str_append(NM_STR_C, str, args[i]);
    }

    nm_str_append(NM_STR, str, str2);

    printf("size: %llu -> %s\n", nm_str_size(str), str);

    nm_str_dispose(str);
    return 0;
}