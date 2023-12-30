#ifndef NAMI_CORE_H
#define NAMI_CORE_H

/* ------ Macros & Defines ----------------
 * ----------------------------------------
*/

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

#define NM_STATIC_ASSERT(expr, msg) _Static_assert(expr, msg)

#define nm_nptr_t ((void*)0)

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef signed char      i8;
typedef signed short     i16;
typedef signed int       i32;
typedef signed long long i64;

typedef float  f32;
typedef double f64;
typedef char   c8;

#endif // NAMI_CORE_H