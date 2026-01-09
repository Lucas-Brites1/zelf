#include "zelf_core_context.h"

void zelf_context_constructor(zmem_arena *arena, zelf_context **out_zctx,
                              zmem_arena *work_arena, zmem_arena *out_arena,
                              zlogger *logger, zstate_info *state) {
  if (!arena) {
    ZERROR("Arena null pointer while trying to create zelf context");
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  if (!out_zctx) {
    ZERROR("Invalid out zelf context pointer");
    zstate_set(Z_ERR_NULL_OUT_PTR);
    return;
  }

  alloc(arena, (*out_zctx), zelf_context, Z8_ALIGNMENT);
  if (!(*out_zctx)) {
    ZERROR("Failed");
    zstate_set(Z_ERR_ALLOC);
    return;
  }

  if (!work_arena || !out_arena || !logger || !state) {
    ZERROR("Invalid dependencies while creating zelf context");
    zstate_set(ZCONTEXT_ERR_INVALID_DEP);
    return;
  }

  (*out_zctx)->work_arena = work_arena;
  (*out_zctx)->out_arena = out_arena;
  (*out_zctx)->logger = logger;
  (*out_zctx)->state_info = state;
  zstate_ok();
}

// inicializar global context corretamente, impl string resto, arrumar log,
// macros de assert, macros para setar pegar valores globais
