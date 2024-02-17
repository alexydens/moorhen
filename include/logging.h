/* Include guard */
#if !defined (MH_LOGGING_H)
#define MH_LOGGING_H

/* To suppress a compiler warning */
#if defined (COMPILER_GCC)
#pragma GCC system_header
#endif

/* Assert onfail updated to use fatal */
#undef ASSERT_ONFAIL
#define ASSERT_ONFAIL(EXPR) log_fatal("Assertion failed: %s", #EXPR);

/* Bool to string with colour */
#define BOOLSTR_COL(BOOL)   ((BOOL) ? \
    "\x1b[0;92mtrue\x1b[0m" : "\x1b[0;91mfalse\x1b[0m")

/* Base library */
#include "base.h"

/* C Stdlib Headers */
#include <stdarg.h>   /* For multiple arguments */
#include <time.h>     /* For current time */
#include <stdio.h>    /* For output to the console and files */

/* Where to log to */
#define LOG_FILE stderr

/* Success */
#define log_success(fmt, ...) _log_success(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
extern void _log_success(const char* file, u64 line, const char* fmt, ...);
/* Info */
#define log_info(fmt, ...) _log_info(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
extern void _log_info(const char* file, u64 line, const char* fmt, ...);
/* Error */
#define log_error(fmt, ...) _log_error(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
extern void _log_error(const char* file, u64 line, const char* fmt, ...);
/* Fatal */
#define log_fatal(fmt, ...) _log_fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
extern void _log_fatal(const char* file, u64 line, const char* fmt, ...);

/* Inlines */
#define log_newline() fprintf(LOG_FILE, "\n");
#define log(fmt, ...) fprintf(LOG_FILE, fmt, ##__VA_ARGS__)

#endif /* MH_LOGGING_H */
