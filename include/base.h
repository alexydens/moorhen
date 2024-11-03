/* Include guard */
#ifndef MH_BASE_H
#define MH_BASE_H

/* --- TYPES --- */

/* UNSIGNED INTEGERS */
/* An 8-bit unsigned integer */
typedef unsigned char       u8;
/* A 16-bit unsigned integer */
typedef unsigned short      u16;
/* A 32-bit unsigned integer */
typedef unsigned int        u32;
/* A 64-bit unsigned integer */
typedef unsigned long long  u64;

/* SIGNED INTEGERS */
/* An 8-bit signed integer */
typedef signed char         i8;
/* A 16-bit signed integer */
typedef signed short        i16;
/* A 32-bit signed integer */
typedef signed int          i32;
/* A 64-bit signed integer */
typedef signed long long    i64;

/* FLOATING POINTS */
/* A 32-bit floating point number */
typedef float               f32;
/* A 64-bit floating point number */
typedef double              f64;

/* SIZE TYPES */
#ifdef MOORHEN_SIZE_64
/* A size type */
typedef u64                 size_t;
/* A signed size type */
typedef i64                 ssize_t;
#else
#ifdef MOORHEN_SIZE_32
/* A size type */
typedef u32                 size_t;
/* A signed size type */
typedef i32                 ssize_t;
#else
/* A size type */
typedef u64                 size_t;
/* A signed size type */
typedef i64                 ssize_t;
#define MOORHEN_SIZE_64
#endif
#endif

/* BOOLEANS */
#ifndef MOORHEN_INCLUDE_STDLIB
/* A boolean */
typedef u8                  bool;
enum { false, true };
#endif

/* --- STATIC ASSERT SIZES --- */
/* Unsigned integers */
_Static_assert(sizeof(u8) == 1, "Moorhen: Wrong size for u8!");
_Static_assert(sizeof(u16) == 2, "Moorhen: Wrong size for u16!");
_Static_assert(sizeof(u32) == 4, "Moorhen: Wrong size for u32!");
_Static_assert(sizeof(u64) == 8, "Moorhen: Wrong size for u64!");
/* Signed integers */
_Static_assert(sizeof(i8) == 1, "Moorhen: Wrong size for i8!");
_Static_assert(sizeof(i16) == 2, "Moorhen: Wrong size for i16!");
_Static_assert(sizeof(i32) == 4, "Moorhen: Wrong size for i32!");
_Static_assert(sizeof(i64) == 8, "Moorhen: Wrong size for i64!");
/* Floats */
_Static_assert(sizeof(f32) == 4, "Moorhen: Wrong size for f32!");
_Static_assert(sizeof(f64) == 8, "Moorhen: Wrong size for f64!");

/* --- ATTRIBUTES --- */
/* Packed structs */
#ifdef __GNUC__
#define __packed __attribute__((packed))
#else
#error "Moorhen: Unrecognized compiler!"
#define __packed
#endif
/* Align on boundary */
#ifdef __GNUC__
#define __aligned(x) __attribute__((aligned(x)))
#else
#error "Moorhen: Unrecognized compiler!"
#define __aligned(x)
#endif
/* Put in specific linker section (and mark as used) */
#ifdef __GNUC__
#define __section(x) __attribute__((used, section(x)))
#else
#error "Moorhen: Unrecognized compiler!"
#define __section(x)
#endif

/* --- MACROS AND CONSTS --- */

/* Get the number of elements in an array */
#define ARRLEN(x)   (sizeof(x) / sizeof(x[0]))
/* Swap two variables */
#define SWAP(x, y)  do { __typeof(x) tmp = x; x = y; y = tmp; } while (0)
/* Get maximum value */
#define MAX(x, y)   ((x) > (y) ? (x) : (y))
/* Get minimum value */
#define MIN(x, y)   ((x) < (y) ? (x) : (y))
/* Get the absolute value of a number */
#define ABS(x)      ((x) < 0 ? -(x) : (x))
/* Clamp a value */
#define CLAMP(x, min, max) MAX(min, MIN(x, max))

/* Pi */
#define PI                 3.14159265358979323846
/* Euler's number */
#define EULER              2.71828182845904523536
/* Size prefixes */
/* One Kibibyte */
#define KiB                1024
/* One Mebibyte */
#define MiB                (1024 * 1024)
/* One Gibibyte */
#define GiB                (1024 * 1024 * 1024)
/* One Tebibyte */
#define TiB                (1024 * 1024 * 1024 * 1024)
/* Minimum and maximum for each type */
/* Max value of u8 */
#define MAX_U8             0xFF
/* Max value of u16 */
#define MAX_U16            0xFFFF
/* Max value of u32 */
#define MAX_U32            0xFFFFFFFF
/* Max value of u64 */
#define MAX_U64            0xFFFFFFFFFFFFFFFF
/* Min value of i8 */
#define MIN_I8             -128
/* Max value of i8 */
#define MAX_I8             127
/* Min value of i16 */
#define MIN_I16            -32768
/* Max value of i16 */
#define MAX_I16            32767
/* Min value of i32 */
#define MIN_I32            -2147483648
/* Max value of i32 */
#define MAX_I32            2147483647
/* Min value of i64 */
#define MIN_I64            -9223372036854775808
/* Max value of i64 */
#define MAX_I64            9223372036854775807
/* Infinity */
#define INFINITY           (1.0 / 0.0)
/* Negative infinity */
#define NEG_INFINITY       (-1.0 / 0.0)
/* NaN */
#define NAN                (0.0 / 0.0)
#ifndef MOORHEN_INCLUDE_STDLIB
/* A null pointer */
#define NULL               ((void*)0)
#endif

/* --- STRUCTS AND ENUMS --- */
/* A buffer */
struct buffer {
  union {
    /* The buffer data */
    void *data;
    /* The buffer data as an array of characters */
    char *char_data;
  };
  /* The size (in bytes) of the buffer */
  size_t size;
};
/* A 2d buffer */
struct buffer2d {
  /* The data */
  void *data;
  /* The width of the buffer */
  size_t width;
  /* The height of the buffer */
  size_t height;
  /* The number of bytes per entry in the buffer */
  u8 entry_size;
};

#ifndef MOORHEN_INCLUDE_STDLIB
/* --- FUNCTIONS REQUIRED BY COMPILER --- */
/*
 * GCC and Clang both use these functions regardless of whether or not they are
 * implemented, so it is a good idea to always have them defined somewhere
 */
/* Memcpy */
static inline void *memcpy(void *dst, const void *src, u32 size) {
  if (!dst || !src) return NULL;
  if (!size) return dst;
  for (u32 i = 0; i < size; i++) ((u8 *)dst)[i] = ((u8 *)src)[i];
  return dst;
}
/* Memset */
static inline void *memset(void *dst, u8 val, u32 size) {
  if (!dst) return NULL;
  if (!size) return dst;
  for (u32 i = 0; i < size; i++) ((u8 *)dst)[i] = val;
  return dst;
}
/* Memmove */
static inline void *memmove(void *dst, const void *src, u32 size) {
  if (!dst || !src) return NULL;
  if (!size) return dst;
  for (u32 i = 0; i < size; i++) ((u8 *)dst)[i] = ((u8 *)src)[i];
  return dst;
}
/* Memcmp */
static inline int memcmp(const void *a, const void *b, u32 size) {
  if (!a || !b) return 0;
  if (!size) return 0;
  for (u32 i = 0; i < size; i++) if (((u8 *)a)[i] != ((u8 *)b)[i]) return 1;
  return 0;
}
#endif

#endif /* MH_BASE_H */
