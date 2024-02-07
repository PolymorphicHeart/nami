#include <nami/entry.h>
#include <nami/str.h>
#include <nami/memory.h>
#include <nami/io.h>

#include "test.h"

void test_destructor (void* ptr)
{
    printf("%s\n", ((nm_str*)ptr)->buf);
}

i32 nm_main (nm_vec(const c8*) args)
{
    //nm_uptr(i32*) example = nm_nptr;

    nm_uptr(nm_str) sptr = nm_make_unique(nm_str, test_destructor);
    sptr->buf = "hello world";
    sptr->len = 12;

    nm_str str1 = nm_str_new("Hello ");
    nm_str str2 = nm_str_new("World");
    nm_str str3 = nm_str_move(str2);

    nm_str_cat(str1, str2);
    nm_str_cat(str1, str3);
    nm_str_cat(str1, nm_str_lit(" - Wait not yet"));

    //printf("%s\n", str1.buf);

    return 0;
}