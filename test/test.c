#include <nami/entry.h>
#include "test.h"

i32 nm_main (nm_vec(const c8*) args)
{
    nm_vec_foreach(const c8* arg, args, 
    {
        printf("%s\n", arg);
    });

    return 0;
}