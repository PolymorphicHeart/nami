#include <nami/entry.h>
#include <stdio.h>

i32 nm_main (const c8** args)
{
    for (u64 i = 0; i < nm_array_count(args); i++)
    {
        printf("%s\n", args[i]);
    }

    return 0;
}