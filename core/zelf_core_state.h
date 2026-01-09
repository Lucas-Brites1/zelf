#ifndef ZELF_CORE_STATE_H
#define ZELF_CORE_STATE_H
#include "zelf_core_types.h"

typedef enum {
  Z_INITIAL = 0,

  Z_SUCCESS,
  Z_ERR_NULL_PTR,
  Z_ERR_NULL_OUT_PTR,
  Z_ERR_NULL_FIELD,
  Z_ERR_ALLOC,
  Z_ERR_OUT_OF_BOUNDS,
  Z_ERR_INVALID_ARG,

  ZARENA_ERR_INVALID_CAP,
  ZARENA_ERR_BLOCK_FULL,
  ZARENA_ERR_ALLOC_NEW_BLOCK,
  ZARENA_ERR_ALLOC_ARENA,

  ZSTR_ERR_EMPTY,
  ZSTR_ERR_INVALID_RANGE,
  ZSTR_ERR_INVALID_CSTR,

  ZFILE_ERR_NULL_ARGVS,
  ZFILE_ERR_ZERO_ARGC,
  ZFILE_ERR_UNDEFINED_FILE_SIZE,
  ZFILE_ERR_FAILED_TO_OPEN,
  ZFILE_ERR_READ_FAILED
} zstate_e;

typedef struct zstate_info {
  zstate_e code;
  const char *func;
  size line;
} zstate_info;

static zstate_info g_zstate = {.code = Z_INITIAL, .func = "", .line = 0};

#define zstate_set(STATE)                                                      \
  do {                                                                         \
    g_zstate.code = STATE, g_zstate.func = __func__;                           \
    g_zstate.line = __LINE__;                                                  \
  } while (0)

#define zstate_ok() (g_zstate.code = Z_SUCCESS)
#define zstate_get (g_zstate.code)
#define zstate_is_ok (g_zstate.code == Z_SUCCESS ? true : false)

#endif // !ZELF_CORE_STATE_H
