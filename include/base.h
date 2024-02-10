/*
 * To define:
 * ENABLE_ASSERT:
 * - if defined, assertions are used. otherwise, they are not
 * ASSERT_ONFAIL:
 * - defines a custom behavior on the failure of an assertions
 */

/* Include guard */
#if !defined (MH_BASE_H)
#define MH_BASE_H

/* Make sure structures take up the smallest space possible */
#pragma pack(1)

/* Standard library headers */
#include <stdlib.h>   /* For exit() and EXIT_FAILURE */
#include <string.h>   /* For strcmp() and strerror() */
#include <errno.h>    /* For errno */
#include <stdint.h>   /* For integer types */
#include <stdbool.h>  /* For booleans */
#include <math.h>     /* For math functions, more float consts */
#include <float.h>    /* For float consts */

/* SIMPLE TYPES */
/* Integers */
typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;
/* Unsigned Integers */
typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;
/* Floats */
typedef float     f32;
typedef double    f64;

/* HELPER MACROS */
/* Make a macro behave more like a function */
#define AS_STMT(S)          do{S}while(0)

/* Clamp v to the range min - max */
#define CLAMP(V, MIN, MAX)  ((V) < (MIN) ? (MIN) : ((V) > (MAX) ? (MAX) : (V)))
/* Swap the values of the two variables */
#define SWAP(A, B)          AS_STMT( __typeof__(A) TMP = (A); A = (B); B = TMP; )
/* Get the bigger of the two values */
#define MAX(A, B)           ((A) > (B) ? (A) : (B))
/* Get the minimum of the two values */
#define MIN(A, B)           ((A) < (B) ? (A) : (B))

/* Assertions */
#if defined (ENABLE_ASSERT)
#   define ASSERT(EXPR)     AS_STMT(if (!(EXPR)) ASSERT_ONFAIL(EXPR);)
#else
#   define ASSERT(EXPR)     ;
#endif

/* Assertion onfail */
#if defined (ENABLE_ASSERT) && !defined(ASSERT_ONFAIL)
#   define ASSERT_ONFAIL(EXPR) exit(EXIT_FAILURE);
#endif

/* COMPILER */
/* Check for GNU C Compiler */
#if defined (__GNUC__)
#   define COMPILER_GCC        1
#endif
/* Check for Microsoft Visual C/C++ */
#if defined (_MSC_VER)
#   define COMPILER_MSVC       1
#endif

/* Put all unset to 0 */
#if !defined (COMPILER_GCC)
#   define COMPILER_GCC        0
#endif
#if !defined (COMPILER_MSVC)
#   define COMPILER_MSVC       0
#endif

/* ARCHITECTURE */
/* As defined by the GNU C Compiler */
#if defined (COMPILER_GCC)
#   if defined (__amd64__)
#     define CPU_AMD64         1
#   endif
#   if defined (__arm__)
#     define CPU_ARM           1
#   endif
#   if defined (__aarch64__)
#     define CPU_ARM64         1
#   endif
#   if defined (__i386__) || defined (__i486__) || defined (__i586__)\
  || defined (__i686__)
#     define CPU_X86           1
#   endif
#endif
/* As defined by the Microsoft Visual C/C++ compiler */
#if defined (COMPILER_MSVC)
#   if defined (_M_AMD64)
#     define CPU_AMD64         1
#   endif
#   if defined (_M_ARM)
#     define CPU_ARM           1
#   endif
#   if defined (_M_ARM64)
#     define CPU_ARM64         1
#   endif
#   if defined (_M_I86) || defined (_M_IX86)
#     define CPU_X86           1
#   endif
#endif
/* Put all uset to 0 */
#if !defined (CPU_AMD64)
#   define CPU_AMD64           0
#endif
#if !defined (CPU_ARM)
#   define CPU_ARM             0
#endif
#if !defined (CPU_ARM64)
#   define CPU_ARM64           0
#endif
#if !defined (CPU_X86)
#   define CPU_X86             0
#endif

/* OPERATING SYSTEM */
#if defined (__gnu_linux__)
#   define OS_LINUX            1
#endif
#if defined (__APPLE__) /* I have reason to believe this is just for GCC... */
#   define OS_MACOS            1
#endif
#if defined (_WIN32)
#   define OS_WINDOWS          1
#endif
/* Put all unset to 0 */
#if !defined (OS_LINUX)
#   define OS_LINUX            0
#endif
#if !defined (OS_MACOS)
#   define OS_MACOS            0
#endif
#if !defined (OS_WINDOWS)
#   define OS_WINDOWS          0
#endif

/* CONSTS */
/* signed int min vals */
static i8   min_i8  = (i8) 0x80;
static i16  min_i16 = (i16)0x8000;
static i32  min_i32 = (i32)0x80000000;
static i64  min_i64 = (i64)0x8000000000000000lu;
/* signed int max vals */
static i8   max_i8  = (i8) 0x7f;
static i16  max_i16 = (i16)0x7fff;
static i32  max_i32 = (i32)0x7fffffff;
static i64  max_i64 = (i64)0x7ffffffffffffffflu;
/* unsigned int max vals */
static u8   max_u8  = (u8) 0xff;
static u16  max_u16 = (u16)0xffff;
static u32  max_u32 = (u32)0xffffffff;
static u64  max_u64 = (u64)0xfffffffffffffffflu;

/* CONVERSIONS */
/* Bool to string */
#define BOOLSTR(BOOL) ((BOOL) ? "true" : "false")
/* String to bool */
#define STRBOOL(STR) (strcmp(STR, "true") == 0)

#endif /* MH_BASE_H */
