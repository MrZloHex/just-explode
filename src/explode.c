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
   static size_t sel = 0;
    switch (exp->state)
    {
        case START_MENU:
            switch (screen_start_menu(exp->screen, sel))
            {
                case SM_NEW_GAME:
                    exp->state = SETUP_GAME;
                    break;
                case SM_CONTINUE:
                    sel = 1;
                    break;
                case SM_EXIT:
                    return false;
            }
            return true;
        case SETUP_GAME:
            switch (screen_setup_game(exp->screen))
            {
                case SGM_PLAY:
                    break;
                case SGM_BACK:
                    exp->state = START_MENU;
            }
            return true;
        case NEW_GAME:
            return true;
        case GAME:
            return true;
        case SETTINGS:
            return false;
    }
    return false;
}