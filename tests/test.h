#ifndef TEST_H
#define TEST_H

#include "nami/nm_core.h"

#define ASSERT_TEST(expr, msg_fail)             \
{                                               \
    if (expr) {}                                \
    else                                        \
    {                                           \
        printf                                  \
        (                                       \
            "assert test failed -> %s\n\t"      \
            "file: %s\n\tline: %d\n\t"          \
            "func: %s\n"                        \
            #expr, __FILE__, __LINE__, __FUNC__ \
        );                                      \
        NM_BREAKPOINT;                          \
    }                                           \
}

#endif // TEST_H