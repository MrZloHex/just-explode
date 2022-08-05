#include "explode.h"

Explode *
explode_initialize()
{
    Explode *exp = (Explode *)malloc(sizeof(Explode));

    exp->state = START_MENU;
    exp->screen = screen_initialize();
    exp->field = NULL;

    return exp;
}


void
explode_deinitialize(Explode *exp)
{
    screen_deinitialize(exp->screen);
    free(exp);
}


bool
explode_run(Explode *exp)
{
    switch (exp->state)
    {
        case START_MENU:
            switch (screen_start_menu(exp->screen))
            {
                case SM_NEW_GAME:
                    break;
                case SM_SETTINGS:
                    break;
                case SM_EXIT:
                    return false;
            }
            return true;
        case NEW_GAME:
            return true;
        case GAME:
            return true;
        case SETTINGS:
            return true;
    }
    return false;
}