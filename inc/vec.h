#ifndef __VEC_H__
#define __VEC_H__

#include "stddef.h"

typedef struct IntPair_S
{
    int x, y;
} IntPair;

typedef struct int16_Pair_S
{
    int16_t x;
    int16_t y;
} int16_Pair;

typedef struct SizePair_S
{
    size_t x;
    size_t y;
} SizePair;

#endif /* __VEC_H__ */