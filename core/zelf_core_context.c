#include "zelf_core_context.h"

void zelf_context_constructor(zmem_arena *arena, zelf_context **out_zctx) {
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
}
