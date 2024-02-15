/* Include guard */
#if !defined (MH_CHUNK_ALLOC_H)
#define MH_CHUNK_ALLOC_H

/* Base library */
#include "base.h"

/* A pool is a chunk allocator */
typedef struct {
  u8* start;      /* The start of the pool allocator */
  bool* used;     /* The used chunks */
  u64 chunk_size; /* The size of the one chunk */
  u64 num_chunks; /* The number of chunks */
} pool_alloc_t;

/* Create a pool allocator (fixed-size chunk allocation) */
extern pool_alloc_t create_pool(u64 c_size, u64 c_num);
/* Destroy a pool allocator */
extern void destroy_pool(pool_alloc_t* pool);
/* Allocate a chunk on a pool allocator */
extern u8* pool_alloc(pool_alloc_t* pool);
/* Free a chunk on a pool allocator */
extern void pool_free(pool_alloc_t* pool, u8* chunk);

#endif /* MH_CHUNK_ALLOC_H */
