#ifndef ZELF_CORE_CONTEXT_H
#define ZELF_CORE_CONTEXT_H

#include "zelf_core_arena.h"
#include "zelf_core_asserts.h"
#include "zelf_core_log.h"

// global context getter by field name
#define ZCTX_GET(name) (zelf_##name##_ctx())

typedef struct {
  zmem_arena *work_arena_ctx;
  zmem_arena *out_arena_ctx;

  zlogger *logger_ctx;
  zstate_info *state_info_ctx;
} zelf_context;

extern zelf_context *g_zelf_ctx;

void zelf_context_constructor(zmem_arena *arena, zmem_arena *work_arena,
                              zmem_arena *out_arena, zlogger *logger,
                              zstate_info *state);

void zelf_context_destructor(zelf_context *ctx);

static inline zmem_arena *zelf_work_arena_ctx(void) {
  zassert_not_null(g_zelf_ctx, dummy, 0, "Zelf context not initialized", true);
  zassert_not_null(g_zelf_ctx->work_arena_ctx, dummy, 0,
                   "Zelf context not initialized succesfully", true);
  return g_zelf_ctx->work_arena_ctx;
}

static inline zmem_arena *zelf_out_arena_ctx(void) {
  zassert_not_null(g_zelf_ctx, dummy, 0, "Zelf context not initialized", true);
  zassert_not_null(g_zelf_ctx->out_arena_ctx, dummy, 0,
                   "Zelf context not initialized succesfully", true);
  return g_zelf_ctx->out_arena_ctx;
}

static inline zlogger *zelf_logger_ctx(void) {
  zassert_not_null(g_zelf_ctx, dummy, 0, "Zelf context not initialized", true);
  zassert_not_null(g_zelf_ctx->logger_ctx, dummy, 0,
                   "Zelf context not initialized succesfully", true);
  return g_zelf_ctx->logger_ctx;
}

static inline zstate_info *zelf_state_info_ctx(void) {
  zassert_not_null(g_zelf_ctx, dummy, 0, "Zelf context not initialized", true);
  zassert_not_null(g_zelf_ctx->state_info_ctx, dummy, 0,
                   "Zelf context not initialized succesfully", true);
  return g_zelf_ctx->state_info_ctx;
}

#endif // !ZELF_CORE_CONTEXT_H
