#ifndef __EXPLODE_H__
#define __EXPLODE_H__

#include "mine.h"
#include "screen.h"
#include "settings.h"

typedef enum ExplodeState_E
{
    START_MENU,
    NEW_GAME,
    SETUP_GAME,
    GAME,
    SETTINGS
} ExplodeState;

typedef struct Explode_S
{
    ExplodeState state;
    Field *field;
    Screen *screen;
    Settings *settings;
} Explode;

Explode *
explode_initialize();

void
explode_deinitialize(Explode *exp);

bool
explode_run(Explode *exp);

#endif /* __EXPLODE_H__ */