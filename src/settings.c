#include "settings.h"

#include "stdlib.h"

Settings *
settings_initiliaze(FieldSize def_size, Difficulty def_dif)
{
    Settings *set = (Settings *)malloc(sizeof(Settings));

    set->diffic = def_dif;
    set->field_size = def_size;

    return set;
}


void
settings_deinitiliaze(Settings *set)
{
    free(set);
}

void
settings_setup(Settings *set, FieldSize size, Difficulty dif)
{
    set->diffic = dif;
    set->field_size = size;
}