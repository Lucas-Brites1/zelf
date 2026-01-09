#ifndef ZELF_CORE_MACROS_H
#define ZELF_CORE_MACROS_H

#ifdef ZELF_INTERNAL
#define new(type, ...) type##_constructor(__VA_ARGS__)
#define create(type, ...) type##_create(__VA_ARGS__)
#define del(type, ...) type##_destructor(__VA_ARGS__)
#define out(type, instance) type instance = null

#define max(a, b) ((a) >= (b) ? (a) : (b))

#define alloc(arena, out, type, align, ...)                                    \
  out = (type *)zmem_arena_alloc(                                              \
      arena, sizeof(type) __VA_OPT__(*(__VA_ARGS__)), align)

#define KiB(n) ((size)1024 * (n))
#define MiB(n) ((size)1024 * 1024 * (n))
#define GiB(n) ((size)1024 * 1024 * 1024 * (n))
#endif

#endif // !ZELF_CORE_MACROS_H
