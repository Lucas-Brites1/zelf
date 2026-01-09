#ifndef ZELF_CORE_CONTEXT_H
#define ZELF_CORE_CONTEXT_H

#include "zelf_core_arena.h"
#include "zelf_core_asserts.h"
#include "zelf_core_log.h"

typedef struct {
  zmem_arena *work_arena;
  zmem_arena *out_arena;

  zlogger *logger;
  zstate_info *state_info;
} zelf_context;

void zelf_context_constructor(zmem_arena *arena, zelf_context **out_zctx,
                              zmem_arena *work_arena, zmem_arena *out_arena,
                              zlogger *logger, zstate_info *state);

#endif // !ZELF_CORE_CONTEXT_H
