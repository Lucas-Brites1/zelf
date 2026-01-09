#include "zelf_core_context.h"

zelf_context *g_zelf_ctx;

void zelf_context_constructor(zmem_arena *arena, zmem_arena *work_arena,
                              zmem_arena *out_arena, zlogger *logger,
                              zstate_info *state) {
  if (!arena) {
    ZDEBUG("Null arena while creating zelf context");
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  alloc(arena, g_zelf_ctx, zelf_context, Z8_ALIGNMENT);
  if (!g_zelf_ctx) {
    ZDEBUG("Failed to alloc zelf context");
    zstate_set(Z_ERR_ALLOC);
    return;
  }

  if (!work_arena || !out_arena || !logger || !state) {
    ZDEBUG("Invalid dependencies while creating zelf context");
    zstate_set(ZCONTEXT_ERR_INVALID_DEP);
    return;
  }

  g_zelf_ctx->work_arena = work_arena;
  g_zelf_ctx->out_arena = out_arena;
  g_zelf_ctx->logger = logger;
  g_zelf_ctx->state_info = state;
  zstate_ok();
}

// inicializar global context corretamente, impl string resto, arrumar log,
// macros de assert, macros para setar pegar valores globais
