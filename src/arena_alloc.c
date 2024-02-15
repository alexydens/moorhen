/* Implements arena_alloc.h, creating and using an arena allocator */
#include <arena_alloc.h>

/*
 * Create an arena of size size bytes. An arena, or linear allocator cannot free
 * a single allocation, but can free all memory at once. Therefore, it is very
 * fast and not very memory efficient
 */
arena_alloc_t create_arena(u64 size) {
  arena_alloc_t arena;
  arena.start = malloc(size);
  arena.current = arena.start;
  arena.size = size;
  ASSERT(size != 0);
  return arena;
}
/* Free all the memory on an arena and set all fields to NULL */
void arena_free(arena_alloc_t* arena) {
  free(arena->start);
  arena->start = NULL;
  arena->current = NULL;
  arena->size = 0;
}
/* Allocate size bytes with the arena */
void* arena_alloc(arena_alloc_t* arena, u64 size) {
  ASSERT(arena->current + size != arena->start + arena->size);
  u8* res = arena->current;
  arena->current += size;
  return res;
}
