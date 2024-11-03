/* Includes */
#define MOORHEN_INCLUDE_STDLIB
#include <base.h>
#include <arena_alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* The tests */
void test_arena_alloc(void) {
  /* Variables */
  struct arena_alloc arena;
  char *ptr;

  /* Message to begin with */
  printf("TESTING: arena_alloc.h\n");

  /* Check invalid arg for arena_init */
  assert(arena_init(0, 0, 0) == MH_ARENA_ALLOC_INVALID_ARG);
  printf("-> PASSED: invalid arg, arena_init\n");
  /* Test arena_init */
  assert(arena_init(&arena, malloc(1024), 1024) == MH_ARENA_ALLOC_SUCCESS);
  printf("-> PASSED: normal usage, arena_init\n");

  /* Check invalid arg for arena_alloc */
  assert(arena_alloc(0, 0, 0) == MH_ARENA_ALLOC_INVALID_ARG);
  printf("-> PASSED: invalid arg, arena_alloc\n");
  /* Test arena_alloc */
  assert(arena_alloc(&arena, (void **)&ptr, 30) == MH_ARENA_ALLOC_SUCCESS);
  printf("-> PASSED: normal usage, arena_alloc (1)\n");
  assert(arena_alloc(&arena, (void **)&ptr, 30) == MH_ARENA_ALLOC_SUCCESS);
  printf("-> PASSED: normal usage, arena_alloc (2)\n");
  assert(arena_alloc(&arena, (void **)&ptr, 1024) == MH_ARENA_ALLOC_OUT_OF_MEMORY);
  printf("-> PASSED: out of memory, arena_alloc\n");

  /* Check invalid arg for arena_free */
  assert(arena_free(0) == MH_ARENA_ALLOC_INVALID_ARG);
  printf("-> PASSED: invalid arg, arena_free\n");
  /* Test arena_free */
  free(arena.base);
  assert(arena_free(&arena) == MH_ARENA_ALLOC_SUCCESS);
  printf("-> PASSED: normal usage, arena_free\n");
}
