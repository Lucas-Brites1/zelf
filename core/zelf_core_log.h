#ifndef ZELF_CORE_LOG_H
#define ZELF_CORE_LOG_H

#include "zelf_core_types.h"
#include <stdlib.h>

// Cores ANSI
#define Z_COLOR_RED "\x1b[31m"
#define Z_COLOR_GREEN "\x1b[32m"
#define Z_COLOR_YELLOW "\x1b[33m"
#define Z_COLOR_BLUE "\x1b[34m"
#define Z_COLOR_RESET "\x1b[0m"
#define Z_STYLE_FILE_META "\x1b[1;3;90m"

typedef enum {
  ZLOG_LEVEL_INFO,
  ZLOG_LEVEL_DEBUG,
  ZLOG_LEVEL_WARN,
  ZLOG_LEVEL_ERROR
} zlog_level_e;

typedef struct {
  boolean enabled;
  boolean enable_debug;
} zlogger;

extern zlogger g_logger;

#define ZLOGGER_ENABLE()                                                       \
  do {                                                                         \
    g_logger.enabled = true;                                                   \
  } while (0)
#define ZLOGGER_ENABLE_DEBUG()                                                 \
  do {                                                                         \
    g_logger.enabled = true;                                                   \
    g_logger.enable_debug = true;                                              \
  } while (0)

void zlog_message(zlog_level_e level, const char *file, int line,
                  const char *fmt, ...);

#define ZINFO(...)                                                             \
  do {                                                                         \
    if (g_logger.enabled)                                                      \
      zlog_message(ZLOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__);          \
  } while (0)
#define ZWARN(...)                                                             \
  do {                                                                         \
    if (g_logger.enabled)                                                      \
      zlog_message(ZLOG_LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__);          \
  } while (0)
#define ZERROR(...)                                                            \
  do {                                                                         \
    if (g_logger.enabled)                                                      \
      zlog_message(ZLOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__);         \
  } while (0)

#ifdef ZELF_DEBUG
#define ZDEBUG(...)                                                            \
  do {                                                                         \
    if (g_logger.enabled && g_logger.enable_debug)                             \
      zlog_message(ZLOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__);         \
  } while (0)
#else
#define ZDEBUG(...)                                                            \
  do {                                                                         \
  } while (0)
#endif

#endif // !ZELF_CORE_LOG_H
