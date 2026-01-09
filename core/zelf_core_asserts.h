#ifndef ZELF_CORE_ASSERTS_H
#define ZELF_CORE_ASSERTS_H

#include "zelf_core_log.h"
#include <stdlib.h>

#define zassert_not_null(ptr, type_to_clean, ptr_to_clean, msg, should_exit)   \
  do {                                                                         \
    if ((ptr) == NULL) {                                                       \
      ZERROR("ASSERT FAILED (Exit: %s): %s", (should_exit) ? "TRUE" : "FALSE", \
             msg);                                                             \
                                                                               \
      del(type_to_clean, ptr_to_clean);                                        \
                                                                               \
      if (should_exit) {                                                       \
        exit(1);                                                               \
      }                                                                        \
    }                                                                          \
  } while (0)

#endif // !ZELF_CORE_ASSERTS_H
