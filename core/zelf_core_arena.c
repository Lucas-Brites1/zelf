#include "zelf_core_arena.h"
#include "zelf_core_log.h"
#include "zelf_core_state.h"
#include "zelf_core_types.h"
#include <stddef.h>
#include <stdlib.h>

static inline size align_up(uaddr addr, zmem_arena_alignment alignment) {
  size mask = (alignment - 1);
  return (addr + mask) & ~(mask);
}

static inline boolean arena_block_has_space(zmem_arena_block *b, size padding,
                                            size space) {
  return b->capacity >= b->used + padding + space;
}

static void arena_insert_new_current_block(zmem_arena *arena, size data_size) {
  size new_cap = max(arena->first->capacity, mult(data_size, 2));
  new_cap = align_up(new_cap, Z64_ALIGNMENT);

  out(zmem_arena_block *, new_curr_block);
  new(zmem_arena_block, &new_curr_block, new_cap);

  if (!new_curr_block) {
    zstate_set(ZARENA_ERR_ALLOC_NEW_BLOCK);
    return;
  }

  arena->current->next = new_curr_block;
  arena->current = new_curr_block;
  zstate_ok();
}

void zmem_arena_block_constructor(zmem_arena_block **out_block, size capacity) {
  if (!out_block) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  if (capacity == 0) {
    zstate_set(ZARENA_ERR_INVALID_CAP);
    return;
  }

  (*out_block) =
      (zmem_arena_block *)calloc(1, sizeof(zmem_arena_block) + capacity);
  if (!(*out_block)) {
    (*out_block) = null;
    zstate_set(Z_ERR_ALLOC);
    return;
  }

  (*out_block)->capacity = capacity;
  (*out_block)->used = 0;
  (*out_block)->next = null;
  zstate_ok();
}

void zmem_arena_constructor(zmem_arena **out_arena, size first_block_capacity) {
  if (!out_arena) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  if (first_block_capacity == 0) {
    zstate_set(ZARENA_ERR_INVALID_CAP);
    return;
  }

  out(zmem_arena_block *, init_block);
  new(zmem_arena_block, &init_block, first_block_capacity);

  if (!init_block) {
    zstate_set(ZARENA_ERR_ALLOC_NEW_BLOCK);
    return;
  }

  (*out_arena) = malloc(sizeof(zmem_arena));
  (*out_arena)->first = init_block;
  (*out_arena)->current = init_block;
  (*out_arena)->bytes_total = 0;
  zstate_ok();
}

void *zmem_arena_alloc(zmem_arena *arena, size size_to_alloc,
                       zmem_arena_alignment align) {
  if (!arena) {
    zstate_set(Z_ERR_NULL_PTR);
    return null;
  }

  if (!arena->current) {
    zstate_set(Z_ERR_NULL_FIELD);
    return null;
  }

  if (size_to_alloc == 0) {
    zstate_set(ZARENA_ERR_INVALID_CAP);
    return null;
  }

  zmem_arena_block *current_used_block = arena->current;

  uaddr current_addr =
      (uaddr)(current_used_block->buff + current_used_block->used);
  size aligned_addr = align_up(current_addr, align);
  size padding_nedeed = aligned_addr - current_addr;

  size total_size = padding_nedeed + size_to_alloc;

  if (!arena_block_has_space(current_used_block, padding_nedeed,
                             size_to_alloc)) {
    arena_insert_new_current_block(arena, total_size);
    if (g_zstate.code != Z_SUCCESS) {
      return null;
    }

    current_used_block = arena->current;
    current_addr = (uaddr)(current_used_block->buff);
    aligned_addr = align_up(current_addr, align);
    padding_nedeed = aligned_addr - current_addr;
    total_size = padding_nedeed + size_to_alloc;
  }

  anyptr result = (anyptr)aligned_addr;
  current_used_block->used += total_size;
  arena->bytes_total += total_size;

  zstate_ok();
  return result;
}

size zmem_arena_used(zmem_arena *arena) {
  if (!arena) {
    zstate_set(Z_ERR_NULL_PTR);
    return 0;
  }

  zstate_ok();
  return arena->bytes_total;
}

void zmem_arena_reset(zmem_arena *arena) {
  if (!arena) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  zmem_arena_block *current = arena->first;
  while (current) {
    current->used = 0;
    current = current->next;
  }

  arena->current = arena->first;
  arena->bytes_total = 0;
  zstate_ok();
}

void zmem_arena_destructor(zmem_arena *arena) {
  ZWARN("Destroying Arena");
  if (!arena) {
    zstate_set(Z_ERR_NULL_PTR);
    return;
  }

  zmem_arena_block *current = arena->first;
  while (current) {
    zmem_arena_block *next = current->next;
    free(current);
    current = next;
  }

  free(arena);
  ZINFO("Arena destroyed succesfully");
  zstate_ok();
}
