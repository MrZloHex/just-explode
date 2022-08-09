#ifndef __TUI_H__
#define __TUI_H__

#include "ncurses.h"

#include "mine.h"
#include "choices.h"
#include "settings.h"

#define AVG_WIN_X(scr) scr->win_size.x / 2
#define AVG_WIN_Y(scr) scr->win_size.y / 2


#define CENTRE_STR(scr, str) AVG_WIN_X(scr) - strlen(str) / 2 -1

#define NEG(e) 0 - e

typedef struct Screen_S
{
    WINDOW *win;
    IntPair win_size;
    SizePair cur_pos;
} Screen;


Screen *
screen_initialize();

void
screen_deinitialize(Screen *screen);

void
print_start_menu(Screen *scr, Field *field);

StartMenu
screen_start_menu(Screen *scr, size_t sel);

SetupGameMenu
screen_setup_game(Screen *scr, Settings *sett);


#endif /* __TUI_H__ */