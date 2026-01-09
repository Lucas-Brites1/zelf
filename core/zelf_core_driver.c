#include "zelf_core_internal.h"

int zelf ZARGS {
  ZLOGGER_ENABLE_DEBUG();

  out(zmem_arena *, work_arena);
  out(zmem_arena *, out_arena);
  new(zmem_arena, &work_arena, MiB(15));
  new(zmem_arena, &out_arena, MiB(25));

  out(zelf_context *, zelf_ctx);
  new(zelf_context, work_arena, &zelf_ctx, work_arena, out_arena, &g_logger,
      &g_zstate);
  zassert_not_null(zelf_ctx, zmem_arena, work_arena,
                   "Failed trying to create zelf context", true);

  out(zargs *, ARGS);
  new(zargs, work_arena, &ARGS, argc, argv);

  zassert_gte(ARGS->count, 1, zmem_arena, work_arena,
              "No input file provided. Usage: zelf <file.zel>", true);

  out(zfile *, ZFILE);
  new(zfile, work_arena, &ZFILE, ARGS);

  zassert_not_null(ZFILE->source, zmem_arena, work_arena,
                   "Failed to read source file", true);

  ZINFO("Compiling file: %s", ZFILE->path);

  printf(zstring_fmt "\n", zstring_args(ZFILE->source));

  del(zmem_arena, work_arena);
  del(zmem_arena, out_arena);
  return g_zstate.code;
}
