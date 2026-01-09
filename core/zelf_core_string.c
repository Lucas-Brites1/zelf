
#include "zelf_core_internal.h"
#include <string.h>

void zstring_constructor(zmem_arena *arena, zstring **out_zstr, size capacity) {
  if (!arena) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  if (!out_zstr) {
    zstate_set(Z_ERR_NULL_OUT_PTR);
    return;
  }

  size zstr_cap = max(capacity, ZSTR_MIN_CAP);

  alloc(arena, (*out_zstr), zstring, Z8_ALIGNMENT);
  if (!(*out_zstr)) {
    zstate_set(Z_ERR_ALLOC);
    return;
  }

  (*out_zstr)->capacity = zstr_cap;
  (*out_zstr)->len = 0;

  alloc(arena, (*out_zstr)->data, u8, Z8_ALIGNMENT, zstr_cap);
  if (!(*out_zstr)->data) {
    zstate_set(Z_ERR_ALLOC);
    return;
  }

  (*out_zstr)->data[0] = NULL_TERMINATOR;
  zstate_ok();
}

void zstring_from_cstr_constructor(zmem_arena *arena, zstring **out_zstr,
                                   const char *cstr) {
  if (!arena) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  if (!out_zstr) {
    zstate_set(Z_ERR_NULL_OUT_PTR);
    return;
  }

  if (!cstr) {
    zstate_set(ZSTR_ERR_INVALID_CSTR);
    return;
  }

  size cstr_len = strlen(cstr);
  zstring_constructor(arena, out_zstr, cstr_len + ZSTR_FROM_CSTR_PAD);
  if (g_zstate.code != Z_SUCCESS) {
    return;
  }

  memcpy((*out_zstr)->data, cstr, cstr_len);
  (*out_zstr)->len = cstr_len;
  (*out_zstr)->data[cstr_len] = NULL_TERMINATOR;

  zstate_ok();
}

void zstring_to_cstr_constructor(zmem_arena *arena, const char **out_cstr,
                                 zstring *zstr) {
  if (!arena) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  if (!out_cstr) {
    zstate_set(Z_ERR_NULL_OUT_PTR);
    return;
  }

  if (!zstr) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  alloc(arena, (*out_cstr), char, Z8_ALIGNMENT, zstr->len + 1);
  if (!(*out_cstr)) {
    zstate_set(Z_ERR_ALLOC);
    return;
  }

  memcpy((char *)(*out_cstr), zstr->data, zstr->len + 1);
  ((char *)(*out_cstr))[zstr->len] = NULL_TERMINATOR;

  zstate_ok();
}
