#include "zelf_core_arena.c"
#include "zelf_core_arena.h"
#include "zelf_core_asserts.h"
#include "zelf_core_file.c"
#include "zelf_core_log.c"
#include "zelf_core_state.h"
#include "zelf_core_string.c"
#include "zelf_core_string.h"
#include <stdio.h>

int main ZARGS {
  out(zmem_arena *, gArena);
  new(zmem_arena, &gArena, MiB(10));

  out(zargs *, ARGS);
  new(zargs, gArena, &ARGS, argc, argv);

  zassert_gte(ARGS->count, 2, zmem_arena, gArena,
              "Failed to initilized CLI arguments context (ZARGS)", true);

  out(zfile *, ZFILE);
  new(zfile, gArena, &ZFILE, ARGS);
  zassert_not_null(ZFILE->source, zmem_arena, gArena,
                   "File param empty or read failed", true);

  out(zstring *, str);
  new(zstring_from_cstr, gArena, &str, "Lucas Silva Brites");

  if (!zstate_is_ok) {
    printf("Erro ao criar string: %d\n", g_zstate.code);
    del(zmem_arena, gArena);
    return g_zstate.code;
  }

  printf(zstring_fmt "\n", zstring_args(str));
  printf(zstring_fmt, zstring_args(ZFILE->source));
  del(zmem_arena, gArena);

  return g_zstate.code;
}
