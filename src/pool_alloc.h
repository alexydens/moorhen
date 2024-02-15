/* Implements chunk_alloc.h */
#include <pool_alloc.h>

/* Create a pool allocator (fixed-size chunk allocation) */
pool_alloc_t create_pool(u64 c_size, u64 c_num) {
  /* The struct */
  pool_alloc_t pool;
  /* Populate fields */
  pool.start = malloc(c_size * c_num);  /* Actual allocation */
  ASSERT(pool.start != NULL);
  pool.used = malloc(sizeof(bool) * c_num);
  ASSERT(pool.used != NULL);
  ASSERT(memset(pool.used, 0x00, sizeof(bool) * c_num));
  pool.chunk_size = c_size;
  pool.num_chunks = c_num;
  return pool;
}
/* Destroy a pool allocator */
void destroy_pool(pool_alloc_t* pool) {
  /* Free vals */
  free(pool->start);
  free(pool->used);
  /* Set all to NULL or 0 */
  pool->start = NULL;
  pool->used = NULL;
  pool->chunk_size = 0;
  pool->num_chunks = 0;
}
/* Allocate a chunk on a pool allocator */
u8* pool_alloc(pool_alloc_t* pool) {
  u64 index_free = 0;
  bool found = false;
  for (u64 i = 0; i < pool->chunk_size; i++) {
    if (!pool->used[i]) {
      index_free = i;
      found = true;
      pool->used[i] = true;
      break;
    }
  }
  ASSERT(found);
  return pool->start + index_free * pool->chunk_size;
}
/* Free a chunk on a pool allocator */
void pool_free(pool_alloc_t* pool, u8* chunk) {
  u64 index = (chunk - pool->start) / pool->chunk_size;
  ASSERT(index < pool->num_chunks);
  pool->used[index] = false;
}
