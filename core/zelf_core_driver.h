#ifndef ZELF_DRIVER_H
#define ZELF_DRIVER_H

#include "zelf_core_arena.c"
#include "zelf_core_asserts.h"
#include "zelf_core_file.c"
#include "zelf_core_log.c"
#include "zelf_core_string.c"
#include "zelf_core_types.h"

#define ZARGS (i8 argc, char **argv)
int zelf ZARGS;

#endif // ZELF_DRIVER_H
