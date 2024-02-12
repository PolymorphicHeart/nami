#ifndef NAMI_ENTRY_H
#define NAMI_ENTRY_H

#include "cont/vec.h"

i32 nm_main (nm_vec(const c8*) args);

i32 main (i32 argc, const c8** argv)
{
    nm_vec(const c8*) args = nm_vec_new_res(const c8*, argc);
    memmove(args, argv, nm_vec_len(args) * sizeof(c8*));

    i32 ret = nm_main(args);

    // is this really needed right before termination?
    nm_vec_free(args);
    return ret;
}

#endif // NAMI_ENTRY_H