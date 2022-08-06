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
screen_start_menu(Screen *screen, size_t sel)
{
    clear();

    attron(A_BOLD);
    mvprintw(AVG_WIN_Y(screen) - 6, AVG_WIN_X(screen) - 7, "JUST EXPLODE");
    attroff(A_BOLD);

    Menu *menu = menu_initialize(sel, false, 3, START_MENU_STRINGS);

    for (;;)
    {
        for (size_t i = 0, off = NEG(menu->q_choices / 2); i < menu->q_choices; ++i, ++off)
        {
            if (i == menu->selected)
                attron(A_BOLD);

            mvprintw(AVG_WIN_Y(screen) + off, CENTRE_STR(screen, menu->choises[i]), "%s", menu->choises[i]);

            if (i == menu->selected)
                attroff(A_BOLD);
        }

        switch (wgetch(stdscr))
        {
            case KEY_DOWN:
            case 's':
            case 'S':
                menu_select_next(menu);
                break;
            case KEY_UP:
            case 'w':
            case 'W':
                menu_select_prev(menu);
                break;
            case KEY_ENTER:
            case 10: 
            {
                StartMenu selected = (StartMenu)menu->selected;
                menu_deinitialize(menu);
                return selected;
            }
        }

        refresh();
    }
}

SetupGameMenu
screen_setup_game(Screen *screen)
{
    clear();

    attron(A_BOLD);
    mvprintw(AVG_WIN_Y(screen) - 6, AVG_WIN_X(screen) - 7, "JUST EXPLODE");
    attroff(A_BOLD);
    
    Menu *menu = menu_initialize(0, true, 4, "Size: < 16x16 >", "Difficulty: < Normal >", "Play!", "Back to main menu");

    for (;;)
    {
        for (size_t i = 0, off = NEG(menu->q_choices / 2); i < menu->q_choices; ++i, ++off)
        {
            if (i == 2)
                off++;
            else if (i == 3)
                off += 3;


            if (i == menu->selected)
                attron(A_BOLD);

            mvprintw(AVG_WIN_Y(screen) + off, CENTRE_STR(screen, menu->choises[i]), "%s", menu->choises[i]);

            if (i == menu->selected)
                attroff(A_BOLD);
        }

        switch (wgetch(stdscr))
        {
            case KEY_DOWN:
            case 's':
            case 'S':
                menu_select_next(menu);
                break;
            case KEY_UP:
            case 'w':
            case 'W':
                menu_select_prev(menu);
                break;
            case KEY_ENTER:
            case 10: 
            {
                SetupGameMenu sel = (SetupGameMenu)menu->selected;
                menu_deinitialize(menu);
                return sel;
            }
        }

        refresh();
    }
}



void
print_start_menu(Screen *scr, Field *field)
{

}