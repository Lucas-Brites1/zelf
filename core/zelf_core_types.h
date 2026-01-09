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

#endif // !ZELF_CORE_TYPES_H
