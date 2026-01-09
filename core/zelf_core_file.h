#ifndef ZELF_CORE_FILE_H
#define ZELF_CORE_FILE_H
#include "zelf_core_arena.h"
#include "zelf_core_string.h"
#include "zelf_core_types.h"

typedef struct {
  int count;
  char **args;
  char *program;
} zargs;

typedef struct {
  zstring *source;
  const char *path;
} zfile;

void zargs_constructor(zmem_arena *arena, zargs **out_zargs, int argc,
                       char **argv);
void zfile_constructor(zmem_arena *arena, zfile **out_zfile, zargs *args);

#endif // !ZELF_CORE_FILE_H
