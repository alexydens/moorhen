/* Include guard */
#if !defined (MH_ARENA_ALLOC_H)
#define MH_ARENA_ALLOC_H

/* Base library */
#include "base.h"

/* An arena is a linear allocator */
typedef struct {
  u8* start;    /* The start of the arena */
  u8* current;  /* The current position of the arena */
  u64 size;     /* The size of the arena */
} arena_alloc_t;

/*
 * Create an arena of size size bytes. An arena, or linear allocator cannot free
 * a single allocation, but can free all memory at once. Therefore, it is very
 * fast and not very memory efficient
 */
extern arena_alloc_t create_arena(u64 size);
/* Free all the memory on an arena and set all fields to NULL */
extern void arena_free(arena_alloc_t* arena);
/* Allocate size bytes with the arena */
extern void* arena_alloc(arena_alloc_t* arena, u64 size);

#endif /* MH_ARENA_ALLOC_H */
