#include "screen.h"
#include "jmenu.h"

#include "string.h"

Screen *
screen_initialize()
{
    Screen *screen = (Screen *)malloc(sizeof(Screen));
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    start_color();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    getmaxyx(stdscr, screen->win_size.y, screen->win_size.x);
    return screen;
}

void
screen_deinitialize(Screen *screen)
{
    endwin();
    free(screen);
}

StartMenu
screen_start_menu(Screen *screen)
{
    attron(A_BOLD);
    mvprintw(AVG_WIN_Y(screen) - 6, AVG_WIN_X(screen) - 7, "JUST EXPLODE");
    attroff(A_BOLD);

    Menu *menu = menu_initialize(0, false, 3, START_MENU_STRINGS);

    for (;;)
    {
        int in_ch = wgetch(stdscr);

        for (size_t i = 0, off = NEG(menu->q_choices / 2); i < menu->q_choices; ++i, ++off)
        {
            if (i == menu->selected)
                attron(A_BOLD);

            mvprintw(AVG_WIN_Y(screen) + off, CENTRE_STR(screen, menu->choises[i]), "%s", menu->choises[i]);

            if (i == menu->selected)
                attroff(A_BOLD);
        }

        if (in_ch == 258)
        {
            menu_select_next(menu);
        }
        else if (in_ch == 259)
        {
            menu_select_prev(menu);
        }
        else if (in_ch == 10)
        {
            StartMenu sel = (StartMenu)menu->selected;
            menu_deinitialize(menu);
            return sel;
        }

        refresh();
    }
}

void
print_start_menu(Screen *scr, Field *field)
{

}