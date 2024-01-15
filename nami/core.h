#ifndef NAMI_CORE_H
#define NAMI_CORE_H

/* ------ Macros & Defines --------------------
 * --------------------------------------------
*/

#if defined(__cplusplus)
# extern "C" {
#endif // __cplusplus

#if defined(_WIN64)
#   define NAMI_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#   define NAMI_PLATFORM_DARWIN
#   define NAMI_PLATFORM_APPLE
#   define NAMI_PLATFORM_UNIX
#elif defined(__linux__)
#   define NAMI_PLATFORM_LINUX
#   define NAMI_PLATFORM_UNIX
#endif // PLATFORMS

#if defined(__amd64__)
#   define NAMI_ARCH_AMD64
#elif defined(__aarch64__)
#   define NAMI_ARCH_ARM64
#endif // ARCHITECTURE

#if defined(NAMI_PLATFORM_WINDOWS)
#   if defined(NAMI_BUILD_SHARED)
#       define NMAPI __declspec(dllexport)
#   else
#       define NMAPI __declspec(dllimport)
#   endif
#else
#   define NMAPI
#endif // EXPORT SYMBOLS

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
# extern "C" }
#endif // __cplusplus

#endif // NAMI_CORE_H