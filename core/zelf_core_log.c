#include "zelf_core_log.h"
#include <stdarg.h>
#include <stdio.h>

zlogger g_logger = {.enabled = true, .enable_debug = false};

void zlog_message(zlog_level_e level, const char *file, int line,
                  const char *fmt, ...) {
  va_list args;

  const char *color = Z_COLOR_RESET;
  const char *label = "INFO";
  FILE *stream = stdout;

  switch (level) {
  case ZLOG_LEVEL_DEBUG:
    color = Z_COLOR_BLUE;
    label = "DEBUG";
    break;
  case ZLOG_LEVEL_WARN:
    color = Z_COLOR_YELLOW;
    label = "WARN";
    break;
  case ZLOG_LEVEL_ERROR:
    color = Z_COLOR_RED;
    label = "ERROR";
    stream = stderr;
    break;
  case ZLOG_LEVEL_INFO:
    color = Z_COLOR_GREEN;
    label = "INFO";
    break;
  }

  fprintf(stream, "%s[%s]%s ", color, label, Z_COLOR_RESET);

  va_start(args, fmt);
  vfprintf(stream, fmt, args);
  va_end(args);

  fprintf(stream, " \t%s(%s:%d)%s\n", Z_STYLE_FILE_META, file, line,
          Z_COLOR_RESET);
}
