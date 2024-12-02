/* Includes */
#define MOORHEN_INCLUDE_STDLIB
#include <base.h>
#include <printf.h>
#include <stdio.h>
#include <assert.h>

/* Putc required */
void _putc(char c) { putchar(c); }

/* The tests */
void test_printf(void) {
  /* Variables */

  /* Message to begin with */
  printf("Testing: printf.h\n");

  /* Test printf normally */
  _printf(_putc, "-> TEST: just a string\n");
  /* Test characters */
  _printf(_putc, "-> TEST: characters (should be a):                 \'%c\'\n", 'a');
  /* Test strings */
  _printf(_putc, "-> TEST: strings (should be hello):                \'%s\'\n", "hello");
  /* Test numbers normally */
  _printf(_putc, "-> TEST: number (should be -1234):                 \'%d\'\n", -1234);
  _printf(_putc, "-> TEST: unsigned (should be 1234):                \'%u\'\n", 1234);
  _printf(_putc, "-> TEST: hex (should be e1a):                      \'%x\'\n", 0xe1a);
  _printf(_putc, "-> TEST: capital hex (should be E1A):              \'%X\'\n", 0xe1a);
  /* Test special formats for numbers */
  _printf(_putc, "-> TEST: number with +/- (should be +1234):        \'%+d\'\n", 1234);
  _printf(_putc, "-> TEST: number with  /- (should be  1234):        \'% d\'\n", 1234);
  _printf(_putc, "-> TEST: number with zeroes (should be 00001234):  \'%08d\'\n", 1234);
  _printf(_putc, "-> TEST: number with padding (should be 1234    ): \'%8d\'\n", 1234);
  _printf(_putc, "-> TEST: hex with base (should be 0xe1a):          \'%#x\'\n", 0xe1a);
  _printf(_putc, "-> TEST: capital hex with base (should be 0xE1A):  \'%#X\'\n", 0xe1a);
  /* Test special formats for strings */
  _printf(_putc, "-> TEST: string with padding (should be hello   ): \'%8s\' (1)\n", "hello");
  _printf(_putc, "-> TEST: string with width (should be hell):       \'%.4s\'     (1)\n", "hello");
  _printf(_putc, "-> TEST: string with padding (should be hello   ): \'%*s\' (2)\n", 8, "hello");
  _printf(_putc, "-> TEST: string with width (should be hell):       \'%.*s\'     (2)\n", 4, "hello");
}
