/* Tests */
extern void test_arena_alloc(void);
extern void test_printf(void);

/* Entry point */
int main(void) {
  /* Run tests */
  test_arena_alloc();
  test_printf();
  return 0;
}
