#ifndef NAMI_CORE_H
#define NAMI_CORE_H

/* ------ Macros & Defines ----------------------
 * ----------------------------------------------
*/

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#if defined(_WIN64)
#   define NM_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#   define NM_PLATFORM_DARWIN
#   define NM_PLATFORM_APPLE
#   define NM_PLATFORM_UNIX
#elif defined(__linux__)
#   define NM_PLATFORM_LINUX
#   define NM_PLATFORM_UNIX
#endif // PLATFORMS

#if defined(__amd64__)
#   define NM_ARCH_AMD64
#elif defined(__aarch64__)
#   define NM_ARCH_ARM64
#endif // ARCHITECTURE

#if defined(NM_PLATFORM_WINDOWS)
#define NM_SYMBOL_EXPORT __declpsec(dllexport)
#define NM_SYMBOL_IMPORT __declspec(dllimport)
#   if defined(NAMI_BUILD_SHARED)
#       define NMAPI NM_SYMBOL_EXPORT
#   else
#       define NMAPI NM_SYMBOL_IMPORT
#   endif
#else
#   define NM_SYMBOL_EXPORT __attribute__((visibility("default")))
#   define NM_SYMBOL_IMPORT
#   define NMAPI
#endif // SYMBOL EXPORTING

#if defined(_MSC_VER)
#   define NM_BREAKPOINT __debugbreak()
#else
#   define NM_BREAKPOINT __builtin_trap()
#endif // BREAKPOINTS

#include <stdio.h>
#include <stdlib.h>

#define NM_STATIC_ASSERT(expr, msg) _Static_assert(expr, msg)

#define nm_nptr_t ((void*)0)

typedef __builtin_va_list nm_vargs_t;

typedef __UINT8_TYPE__   u8;
typedef __UINT16_TYPE__ u16;
typedef __UINT32_TYPE__ u32;
typedef __UINT64_TYPE__ u64;

typedef __INT8_TYPE__   i8;
typedef __INT16_TYPE__ i16;
typedef __INT32_TYPE__ i32;
typedef __INT64_TYPE__ i64;

typedef float  f32;
typedef double f64;
typedef char   c8;

NM_STATIC_ASSERT (sizeof(u8)  == 1, "u8 expected to be 1 byte(s)");
NM_STATIC_ASSERT (sizeof(u16) == 2, "u16 expected to be 2 byte(s)");
NM_STATIC_ASSERT (sizeof(u32) == 4, "u32 expected to be 4 byte(s)");
NM_STATIC_ASSERT (sizeof(u64) == 8, "u64 expected to be 8 byte(s)");

NM_STATIC_ASSERT (sizeof(i8)  == 1, "i8 expected to be 1 byte(s)");
NM_STATIC_ASSERT (sizeof(i16) == 2, "i16 expected to be 2 byte(s)");
NM_STATIC_ASSERT (sizeof(i32) == 4, "i32 expected to be 4 byte(s)");
NM_STATIC_ASSERT (sizeof(i64) == 8, "i64 expected to be 8 byte(s)");

NM_STATIC_ASSERT (sizeof(c8)  == 1, "c8 expected to be 1 byte(s)");
NM_STATIC_ASSERT (sizeof(f32) == 4, "f32 expected to be 4 byte(s)");
NM_STATIC_ASSERT (sizeof(f64) == 8, "f64 expected to be 8 byte(s)");

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // NAMI_CORE_H