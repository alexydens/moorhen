/* Implements logging.h, for logging to console */
#include <logging.h>

/*
 * ESCAPE CODES:
 * in the format '\x1b[a;b;cm' where a, b and c are parameters.
 * PARAMETERS:
 * - 0 resets.
 * - 1 bold.
 * - 3 italic.
 * - 4 underline.
 * FOREGROUND:
 * - 30 black.
 * - 91 red.
 * - 92 green.
 * - 93 yellow.
 * - 94 blue.
 * - 90 gray.
 */
#define TIME_CODE   "\x1b[0m"
#define SOURCE_CODE "\x1b[0;90m"
#define MAIN_CODE   "\x1b[0m"
const char codes[4][10] = {
    "\x1b[0;1;92m",
    "\x1b[0;1;93m",
    "\x1b[0;1;91m",
    "\x1b[0;1;91m",
};

/* For message type */
const char types[4][8] = {
    "SUCCESS",
    "INFO   ",
    "ERROR  ",
    "FATAL  ",
};

/* Used for all log functions */
void log_common(const char* file, u64 line, u8 index) {
  char time_str[1024];
  time_t curr_time = time(NULL);
  struct tm* local_time = localtime(&curr_time);
  strftime(time_str, 1024, "%H:%M:%S", local_time);
  fprintf(
      stdout, "%s%s %s%s %s%s:%lu: %s",
      TIME_CODE, time_str,
      codes[index], types[index],
      SOURCE_CODE, file, line,
      MAIN_CODE
  );
}

/* Success */
void _log_success(const char* file, u64 line, const char* fmt, ...) {
  va_list args;
  log_common(file, line, 0);
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  va_end(args);
  fprintf(stdout, "\x1b[0m\n");
}
/* Info */
void _log_info(const char* file, u64 line, const char* fmt, ...) {
  va_list args;
  log_common(file, line, 1);
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  va_end(args);
  fprintf(stdout, "\x1b[0m\n");
}
/* Error */
void _log_error(const char* file, u64 line, const char* fmt, ...) {
  va_list args;
  log_common(file, line, 2);
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  va_end(args);
  fprintf(stdout, "\x1b[0m\n");
}
/* Fatal */
void _log_fatal(const char* file, u64 line, const char* fmt, ...) {
  va_list args;
  log_common(file, line, 3);
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  va_end(args);
  fprintf(stdout, "\x1b[0m\n");
  exit(EXIT_FAILURE);
}
