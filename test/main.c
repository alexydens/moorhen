/* Base library */
#include <base.h>
#include <logging.h>
#include <arena_alloc.h>
#include <pool_alloc.h>

/* Testing... */
void test_base();
void test_arena_alloc();
void test_pool_alloc();

/* Entry point */
i32 main() {
  test_base();
  test_arena_alloc();
  test_pool_alloc();
  return 0;
}

/* Test base.h */
void test_base() {
  log_info("Compiler GCC:\t%s", BOOLSTR_COL(COMPILER_GCC));
  log_info("Compiler MSVC:\t%s", BOOLSTR_COL(COMPILER_MSVC));
  log_newline();
  log_info("OS Windows:\t%s", BOOLSTR_COL(OS_WINDOWS));
  log_info("OS Linux:  \t%s", BOOLSTR_COL(OS_LINUX));
  log_info("OS MacOS:  \t%s", BOOLSTR_COL(OS_MACOS));
  log_newline();
  log_info("CPU x86:  \t%s", BOOLSTR_COL(CPU_X86));
  log_info("CPU Arm:  \t%s", BOOLSTR_COL(CPU_ARM));
  log_info("CPU Arm64:\t%s", BOOLSTR_COL(CPU_ARM64));
  log_info("CPU Amd64:\t%s", BOOLSTR_COL(CPU_AMD64));
  log_newline();
  ASSERT(CLAMP(-1, 0, 10) == 0);
  log_success("CLAMP(): below range.");
  ASSERT(CLAMP(11, 0, 10) == 10);
  log_success("CLAMP(): above range.");
  ASSERT(CLAMP(5, 0, 10) == 5);
  log_success("CLAMP(): within range");
  log_newline();
  do {
    i8 a = 'a';
    i8 b = 'b';
    SWAP(a, b);
    ASSERT(a == 'b' && b == 'a');
    log_success("SWAP().");
  } while(0);
  log_newline();
  ASSERT(MAX(0, 5) == 5);
  log_success("MAX(): Second val.");
  ASSERT(MAX(5, 0) == 5);
  log_success("MAX(): First val.");
  ASSERT(MAX(5, 5) == 5);
  log_success("MAX(): Same val.");
  log_newline();
}
void test_arena_alloc() {
  /* TODO */
}
void test_pool_alloc() {
  /* TODO */
}
