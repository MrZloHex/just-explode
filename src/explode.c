#include "explode.h"

Explode *
explode_initialize()
{
    Explode *exp = (Explode *)malloc(sizeof(Explode));

    exp->state = START_MENU;
    exp->screen = screen_initialize();
    exp->field = NULL;
    exp->settings = settings_initiliaze(NORMAL, S10_10);

    return exp;
}


void
explode_deinitialize(Explode *exp)
{
    screen_deinitialize(exp->screen);
    settings_deinitiliaze(exp->settings);
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
                    break;
                case SM_EXIT:
                    return false;
            }
            return true;
        case SETUP_GAME:
            switch (screen_setup_game(exp->screen, exp->settings))
            {
                case SGM_PLAY:
                    exp->state = NEW_GAME;
                    break;
                case SGM_BACK:
                    exp->state = START_MENU;
            }
            return true;
        case NEW_GAME:
            exp->field = field_initialize(k_sizes[exp->settings->field_size]);
            field_generate(exp->field, exp->settings->diffic);
            exp->state = GAME;
            return true;
        case GAME:
            return true;
        case SETTINGS:
            return false;
    }
    return false;
}