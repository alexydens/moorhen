/* Base library */
#include <base.h>
#include <logging.h>

/* Entry point */
i32 main() {
  log_info("OS Windows:\t%s", BOOLSTR(OS_WINDOWS));
  log_info("OS Linux:  \t%s", BOOLSTR(OS_LINUX));
  log_info("OS MacOS:  \t%s", BOOLSTR(OS_MACOS));
  log_newline();
  log_info("CPU x86:  \t%s", BOOLSTR(CPU_X86));
  log_info("CPU Arm:  \t%s", BOOLSTR(CPU_ARM));
  log_info("CPU Arm64:\t%s", BOOLSTR(CPU_ARM64));
  log_info("CPU Amd64:\t%s", BOOLSTR(CPU_AMD64));
  log_newline();
  return 0;
}
