#ifndef ZELF_CORE_TYPES_H
#define ZELF_CORE_TYPES_H
#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef size_t size;
typedef uintptr_t uaddr;
typedef void *anyptr;

typedef u8 boolean;

#define true 1
#define false 0
#define null ((anyptr)0)

#define new(type, ...) type##_constructor(__VA_ARGS__)
#define create(type, ...) type##_create(__VA_ARGS__)
#define del(type, ...) type##_destructor(__VA_ARGS__)
#define out(type, instance) type instance = null

#define max(a, b) ((a) >= b) ? (a) : (b)
#define mult(n, by) ((n) * (by))

#endif // !ZELF_CORE_TYPES_H
