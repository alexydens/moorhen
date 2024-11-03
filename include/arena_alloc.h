/* Include guard */
#ifndef MH_ARENA_H
#define MH_ARENA_H

/* Includes */
#include "base.h"

/* An arena allocator */
struct arena_alloc {
  /* The start of the memory */
  void *base;
  /* The amount of the memory used */
  size_t used;
  /* The maximum amount of memory that can be used */
  size_t size;
};

/* Errors from arena allocator functions */
enum arena_alloc_error {
  /* Success */
  MH_ARENA_ALLOC_SUCCESS,
  /* Invalid argument */
  MH_ARENA_ALLOC_INVALID_ARG,
  /* Out of memory */
  MH_ARENA_ALLOC_OUT_OF_MEMORY,
};

/* Initialize an arena allocator */
enum arena_alloc_error arena_init(
    struct arena_alloc *arena,
    void *base,
    size_t size
) {
  if (!arena || !base || !size) return MH_ARENA_ALLOC_INVALID_ARG;
  arena->base = base;
  arena->used = 0;
  arena->size = size;
  return MH_ARENA_ALLOC_SUCCESS;
}
/* Free an arena allocator */
enum arena_alloc_error arena_free(struct arena_alloc *arena) {
  if (!arena) return MH_ARENA_ALLOC_INVALID_ARG;
  arena->base = NULL;
  arena->used = 0;
  arena->size = 0;
  return MH_ARENA_ALLOC_SUCCESS;
}

/* Allocate on an arena allocator */
enum arena_alloc_error arena_alloc(
    struct arena_alloc *arena,
    void **ptr,
    size_t size
) {
  if (!arena || !ptr || !size) return MH_ARENA_ALLOC_INVALID_ARG;
  if (arena->used + size > arena->size) return MH_ARENA_ALLOC_OUT_OF_MEMORY;
  *ptr = (u8 *)arena->base + arena->used;
  arena->used += size;
  return MH_ARENA_ALLOC_SUCCESS;
}

#endif /* MH_ARENA_H */
