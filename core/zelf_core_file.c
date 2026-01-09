#include "zelf_core_file.h"
#include "zelf_core_arena.h"
#include "zelf_core_state.h"
#include "zelf_core_string.h"
#include "zelf_core_types.h"
#include <stdio.h>
#include <sys/stat.h>

static boolean zfile_get_file_size(const char *path, size *out_size) {
  struct stat st;
  if (stat(path, &st) != 0) {
    return false;
  }
  *out_size = (size)st.st_size;
  return true;
}

static void zfile_read(zmem_arena *arena, zfile *zfile) {
  size file_size;
  if (!zfile_get_file_size(zfile->path, &file_size)) {
    zstate_set(ZFILE_ERR_UNDEFINED_FILE_SIZE);
    return;
  }

  FILE *file = fopen(zfile->path, "rb");
  if (!file) {
    zstate_set(ZFILE_ERR_FAILED_TO_OPEN);
    return;
  }

  alloc(arena, zfile->source, zstring, Z8_ALIGNMENT);
  zfile->source->capacity = file_size + 1;
  alloc(arena, zfile->source->data, u8, Z8_ALIGNMENT, file_size + 1);

  if (!zfile->source->data) {
    fclose(file);
    zstate_set(Z_ERR_ALLOC);
    return;
  }

  size bytes_read = fread(zfile->source->data, 1, file_size, file);
  if (bytes_read != file_size) {
    fclose(file);
    zstate_set(ZFILE_ERR_READ_FAILED);
    return;
  }

  zfile->source->data[file_size] = NULL_TERMINATOR;
  zfile->source->len = file_size;

  fclose(file);
  zstate_ok();
}

void zargs_constructor(zmem_arena *arena, zargs **out_zargs, int argc,
                       char **argv) {
  if (!arena || !out_zargs) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  if (argc == 0) {
    zstate_set(ZFILE_ERR_ZERO_ARGC);
    return;
  }

  if (!argv) {
    zstate_set(ZFILE_ERR_NULL_ARGVS);
    return;
  }

  alloc(arena, (*out_zargs), zargs, Z8_ALIGNMENT);
  if (!out_zargs) {
    zstate_set(Z_ERR_ALLOC);
    return;
  }

  (*out_zargs)->args = argv + 1;
  (*out_zargs)->count = argc - 1;
  (*out_zargs)->program = argv[0];
  zstate_set(Z_SUCCESS);
}

void zfile_constructor(zmem_arena *arena, zfile **out_zfile, zargs *args) {
  if (!arena || !out_zfile || !args) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  alloc(arena, (*out_zfile), zfile, Z8_ALIGNMENT);
  if (!out_zfile) {
    zstate_set(Z_ERR_ALLOC);
    return;
  }

  (*out_zfile)->path = args->args[0];
  zfile_read(arena, *out_zfile);
  if (g_zstate.code != Z_SUCCESS) {
    return;
  }
}
