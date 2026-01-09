#ifndef ZELF_CORE_STRING_H
#define ZELF_CORE_STRING_H
#include "zelf_core_arena.h"
#include "zelf_core_types.h"

#define ZSTR_MIN_CAP 64
#define ZSTR_FROM_CSTR_PAD 16
#define NULL_TERMINATOR '\0'

#define zstring_fmt "%.*s"
#define zstring_args(zstr) (i8)(zstr)->len, (char *)(zstr)->data

typedef struct {
  size capacity;
  size len;
  u8 *data;
} zstring;

typedef struct {
  const char *source;
  size current;
} zstring_cursor;

typedef struct {
  const zstring *source;
  size start;
  size len;
} zstring_view;

void zstring_constructor(zmem_arena *arena, zstring **out_zstr, size capacity);
void zstring_from_cstr_constructor(zmem_arena *arena, zstring **out_zstr,
                                   const char *cstr);
void zstring_to_cstr_constructor(zmem_arena *arena, const char **out_cstr,
                                 zstring *zstr);

size zstring_len(const zstring *zstr);
size zstring_capacity(const zstring *zstr);
boolean zstring_is_empty(const zstring *str);

void zstring_clear(zstring *zstr);
void zstring_append(zmem_arena *arena, zstring *zstr, const char *data);
void zstring_append_char(zmem_arena *arena, zstring *zstr, char c);
void zstring_append_zstr(zmem_arena *arena, zstring *zstr,
                         const zstring *other);
void zstring_write(zmem_arena *arena, zstring *zstr, const char *data);

void zstring_format(zmem_arena *arena, zstring *zstr, const char *fmt, ...);
void zstring_append_format(zmem_arena *arena, zstring *zstr, const char *fmt,
                           ...);

void zstring_concat(zmem_arena *arena, zstring **out_zstr, const zstring *s1,
                    const zstring *s2);
void zstring_subzstring(zmem_arena *arena, zstring **out_zstr,
                        const zstring *zstr, size start, size end);

boolean zstring_equals(const zstring *s1, const zstring *s2);
boolean zstring_equals_cstr(const zstring *zstr, const char *cstr);
i8 zstring_compare(const zstring *s1, const zstring *s2);

i64 zstring_find(const zstring *zstr, const char *needle);
i64 zstring_find_char(const zstring *zstr, char c);
boolean zstring_contains(const zstring *zstr, const char *needle);
boolean zstring_starts_with(const zstring *zstr, const char *prefix);
boolean zstring_ends_with(const zstring *zstr, const char *suffix);

zstring_view zstring_view_create(const zstring *zstr, size start, size len);
char zstring_view_at(const zstring_view *view, size index);

zstring_cursor zstring_cursor_create(const zstring *zstr);
boolean zstring_cursor_next(zstring_cursor *cursor, char *out_char);
boolean zstring_cursor_has_next(zstring_cursor *cursor);
void zstring_cursor_advance(const zstring_cursor *cursor);
char zstring_cursor_peek(const zstring_cursor *cursor);

#endif // !ZELF_CORE_STRING_H
