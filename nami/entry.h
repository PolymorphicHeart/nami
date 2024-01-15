#ifndef NAMI_ENTRY_H
#define NAMI_ENTRY_H

#include "containers/array.h"

i32 nm_main (const c8** args);

i32 main (i32 argc, const c8** argv)
{
    const c8** args = nm_array_create_reserved(const c8*, argc);
    for (i32 i = 0; i < argc; i++) args[i] = argv[i];

    i32 ret = nm_main(args);
    nm_array_dispose(args);
    
    return ret;
}

#endif // NAMI_ENTRY_H