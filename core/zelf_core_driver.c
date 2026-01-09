#include "zelf_core_internal.h"

int zelf ZARGS {
  out(zmem_arena *, gArena);
  new(zmem_arena, &gArena, MiB(10));

  ZLOGGER_ENABLE_DEBUG();

  out(zargs *, ARGS);
  new(zargs, gArena, &ARGS, argc, argv);

  zassert_gte(ARGS->count, 1, zmem_arena, gArena,
              "No input file provided. Usage: zelf <file.zel>", true);

  out(zfile *, ZFILE);
  new(zfile, gArena, &ZFILE, ARGS);

  zassert_not_null(ZFILE->source, zmem_arena, gArena,
                   "Failed to read source file", true);

  ZINFO("Compiling file: %s", ZFILE->path);

  printf(zstring_fmt "\n", zstring_args(ZFILE->source));

  del(zmem_arena, gArena);

  return g_zstate.code;
}
