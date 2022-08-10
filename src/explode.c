#include "explode.h"

Explode *
explode_initialize()
{
    Explode *exp = (Explode *)malloc(sizeof(Explode));

    exp->state = START_MENU;
    exp->screen = screen_initialize();
    exp->field = NULL;
    exp->settings = settings_initiliaze(S10_10, NORMAL);

    return exp;
}


void
explode_deinitialize(Explode *exp)
{
    screen_deinitialize(exp->screen);
    settings_deinitiliaze(exp->settings);
    field_deinitilize(exp->field);
    free(exp);
}


bool
explode_run(Explode *exp)
{
    static bool gen = true;
    switch (exp->state)
    {
        case START_MENU:
            switch (screen_start_menu(exp->screen))
            {
                case SM_NEW_GAME:
                    exp->state = SETUP_GAME;
                    return true;
                case SM_EXIT:
                    return false;
            }
        case SETUP_GAME:
            gen = true;
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
            exp->state = GAME;
            return true;
        case GAME:
            switch (screen_render_game(exp->screen, exp->field, exp->settings->diffic, gen))
            {
                case GR_GAME_OVER:
                    exp->state = GAME_FINISH;
                    exp->winned = false;
                    break;
                case GR_GAME_WIN:
                    exp->state = GAME_FINISH;
                    exp->winned = true;
                    break;
                case GR_PAUSE:
                    exp->state = GAME_PAUSE;
            }
            return true;
        case GAME_PAUSE:
            switch (screen_game_pause(exp->screen))
            {
                case GPM_RESUME:
                    gen = false;
                    exp->state = GAME;
                    break;

                case GPM_NEW_GAME:
                    field_deinitilize(exp->field);
                    exp->state = SETUP_GAME;
                    break;

                case GPM_EXIT:
                    return false;
            }
            return true;
        case GAME_FINISH:
            switch (screen_game_finish(exp->screen, exp->winned))
            {
                case GFM_NEW_GAME:
                    field_deinitilize(exp->field);
                    exp->state = SETUP_GAME;
                    break;
                case GFM_EXIT:
                    return false;
            }
            return true;
    }
    return false;
}