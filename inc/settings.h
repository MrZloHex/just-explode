#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "vec.h"

typedef enum Difficulty_E
{
    EASY    = 0,
    NORMAL  = 1,
    HARD    = 2,
    Q_DIFS  = 3
} Difficulty;

typedef enum FieldSize_E
{
    S8_8    = 0,
    S10_10  = 1,
    S10_14  = 2,
    S14_18  = 3,
    S16_16  = 4,
    Q_SIZES = 5
} FieldSize;

const static SizePair k_sizes[Q_SIZES] = 
{
    {8, 8},
    {10, 10},
    {10, 14},
    {14, 18},
    {16, 16}
};

typedef struct Settings_S
{
    FieldSize field_size;
    Difficulty diffic;
} Settings;


Settings *
settings_initiliaze(FieldSize def_size, Difficulty def_dif);

void
settings_deinitiliaze(Settings *set);

void
settings_setup(Settings *set, FieldSize size, Difficulty dif);

#endif /* __SETTINGS_H__ */