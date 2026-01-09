#ifndef ZELF_CORE_CONTEXT_H
#define ZELF_CORE_CONTEXT_H

#include "zelf_core_arena.h"
#include "zelf_core_asserts.h"
#include "zelf_core_log.h"

#define ZCONTEXT_GET(name) (zelf_##name())

typedef struct {
  zmem_arena *work_arena;
  zmem_arena *out_arena;

  zlogger *logger;
  zstate_info *state_info;
} zelf_context;

extern zelf_context *g_zelf_ctx;

void zelf_context_constructor(zmem_arena *arena, zmem_arena *work_arena,
                              zmem_arena *out_arena, zlogger *logger,
                              zstate_info *state);

static inline zmem_arena *zelf_work_arena(void) {
  return g_zelf_ctx->work_arena;
}

static inline zmem_arena *zelf_arena_out(void) { return g_zelf_ctx->out_arena; }

static inline zlogger *zelf_logger(void) { return g_zelf_ctx->logger; }

static inline zstate_info *zelf_state_info(void) {
  return g_zelf_ctx->state_info;
}

#endif // !ZELF_CORE_CONTEXT_H
