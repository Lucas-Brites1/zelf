#ifndef ZELF_CORE_ARENA_H
#define ZELF_CORE_ARENA_H
#include "zelf_core_log.h"
#include "zelf_core_macros.h"
#include "zelf_core_state.h"
#include "zelf_core_types.h"
#include <stddef.h>
#include <stdlib.h>

typedef enum {
  Z8_ALIGNMENT = 8,
  Z16_ALIGNMENT = 16,
  Z32_ALIGNMENT = 32,
  Z64_ALIGNMENT = 64
} zmem_arena_alignment;

typedef struct zmem_arena_block {
  size capacity;
  size used;
  struct zmem_arena_block *next;

  u8 buff[];
} zmem_arena_block;

typedef struct zmem_arena {
  zmem_arena_block *first;
  zmem_arena_block *current;
  size bytes_total;
} zmem_arena;

static inline size align_up(uaddr addr, zmem_arena_alignment alignment) {
  size mask = (alignment - 1);
  return (addr + mask) & ~(mask);
}

static inline boolean arena_block_has_space(zmem_arena_block *b, size padding,
                                            size space) {
  return b->capacity >= b->used + padding + space;
}

void zmem_arena_block_constructor(zmem_arena_block **out_block, size capacity);
void zmem_arena_constructor(zmem_arena **out_arena, size first_block_capacity);

void *zmem_arena_alloc(zmem_arena *arena, size size_to_alloc,
                       zmem_arena_alignment align);

size zmem_arena_used(zmem_arena *arena);
void zmem_arena_reset(zmem_arena *arena);
void zmem_arena_destructor(zmem_arena *arena);

#endif // !ZELF_CORE_ARENA_H
