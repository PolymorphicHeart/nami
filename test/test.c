#include <nami/entry.h>
#include <nami/containers/string.h>
#include <nami/terminal.h>

#include <stdio.h>
#include "test.h"

i32 nm_main (const c8** args)
{
    c8* str = nm_str_create(NM_ANSI_COLOR_GREEN"args -> [ ");
    c8* str2 = nm_str_create("]"NM_ANSI_COLOR_RESET"\n");

    for (u64 i = 0; i < nm_array_count(args); i++)
    {
        nm_str_append(NM_STR_C, str, args[i]);
        nm_str_append(NM_STR_C, str, ", ");
    }

    nm_str_append(NM_STR, str, str2);

    printf("");
    return 0;
}