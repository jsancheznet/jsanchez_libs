#pragma once

#define global static
#define internal_variable static

#include <assert.h>
#define Assert assert

#include <stdlib.h>
#define Malloc malloc
#define Free free

#include <stdbool.h>
#include <stdint.h>
typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t    i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;
typedef i32      b32;
typedef u32   shader;

#define ARRAY_SIZE(Array) ((sizeof(Array)) / (sizeof(Array[0])))
