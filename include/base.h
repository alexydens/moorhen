/*
 * To define:
 * DEBUG:
 * - defines ENABLE_ASSERT
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
#include <stdint.h>   /* For integer types */
#include <stdbool.h>  /* For booleans */
#include <stdlib.h>   /* For exit() and EXIT_FAILURE */

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

#endif /* MH_BASE_H */
