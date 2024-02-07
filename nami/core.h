#ifndef NAMI_CORE_H
#define NAMI_CORE_H

/* ------ Macros & Defines ----------------------
 * ----------------------------------------------
*/

#if defined(__cplusplus)
#   define NM_CPP_HEADER_CHECK_START extern "C" {
#   define NM_CPP_HEADER_CHECK_END }
#else
#   define NM_CPP_HEADER_CHECK_START
#   define NM_CPP_HEADER_CHECK_END
#endif // cpp header checks

#if defined(_WIN32)
#   define NM_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
#   define NM_PLATFORM_DARWIN 1
#   define NM_PLATFORM_APPLE  1
#   define NM_PLATFORM_UNIX   1
#   include <TargetConditionals.h>
#   if TARGET_OS_OSX
#       define NM_PLATFORM_APPLE_MACOS 1
#   elif TARGET_OS_IPHONE
#       define NM_PLATFORM_APPLE_IOS 1
#   elif TARGET_OS_SIMULATOR
#       define NM_PLATFORM_APPLE_IOS_SIMULATOR 1
#   endif // APPLE PLATFORMS
#elif defined(__linux__)
#   define NM_PLATFORM_LINUX 1
#   define NM_PLATFORM_UNIX  1
#endif // PLATFORMS

#if defined(__amd64__)
#   define NM_ARCH_X64   1
#   define NM_ARCH_AMD64 1
#   define NM_ARCH_BITS  64u
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#   define NM_ARCH_X86  1
#   define NM_ARCH_BITS 32u
#elif defined(__aarch64__) || defined(_M_ARM64)
#   define NM_ARCH_ARM64 1
#   define NM_ARCH_BITS  64u
#endif // ARCHITECTURE

#if defined(NM_PLATFORM_WINDOWS)
#define NM_SYMBOL_EXPORT __declpsec(dllexport)
#define NM_SYMBOL_IMPORT __declspec(dllimport)
#else
#   define NM_SYMBOL_EXPORT __attribute__((visibility("default")))
#   define NM_SYMBOL_IMPORT
#endif // SYMBOL EXPORTING

#if defined(_MSC_VER)
#   define NM_BREAKPOINT __debugbreak()
#else
#   define NM_BREAKPOINT __builtin_trap()
#endif // BREAKPOINTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef __SIZE_TYPE__ usize;

typedef float  f32;
typedef double f64;
typedef char   c8;

NM_STATIC_ASSERT (sizeof(u8)  == 1, "u8 expected to be 1 byte");
NM_STATIC_ASSERT (sizeof(u16) == 2, "u16 expected to be 2 byte(s)");
NM_STATIC_ASSERT (sizeof(u32) == 4, "u32 expected to be 4 byte(s)");
NM_STATIC_ASSERT (sizeof(u64) == 8, "u64 expected to be 8 byte(s)");

NM_STATIC_ASSERT (sizeof(i8)  == 1, "i8 expected to be 1 byte");
NM_STATIC_ASSERT (sizeof(i16) == 2, "i16 expected to be 2 byte(s)");
NM_STATIC_ASSERT (sizeof(i32) == 4, "i32 expected to be 4 byte(s)");
NM_STATIC_ASSERT (sizeof(i64) == 8, "i64 expected to be 8 byte(s)");

NM_STATIC_ASSERT (sizeof(c8)  == 1, "c8 expected to be 1 byte");
NM_STATIC_ASSERT (sizeof(f32) == 4, "f32 expected to be 4 byte(s)");
NM_STATIC_ASSERT (sizeof(f64) == 8, "f64 expected to be 8 byte(s)");

#endif // NAMI_CORE_H