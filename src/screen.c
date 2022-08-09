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

    Menu *menu = menu_initialize
    (
        sel, false, 3,
        variant_new("New Game", 0, 0),
        variant_new("Continue", 0, 0),
        variant_new("Exit", 0, 0)
    );

    for (;;)
    {
        for (size_t i = 0, off = NEG(menu->q_variants/ 2); i < menu->q_variants; ++i, ++off)
        {
            if (i == menu->selected)
                attron(A_BOLD);

            char *choice = variant_display(menu_get_variant(menu, i));
            mvprintw(AVG_WIN_Y(screen) + off, CENTRE_STR(screen, choice), "%s", choice);
            free(choice);

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
screen_setup_game(Screen *screen, Settings *sett)
{
    clear();

    attron(A_BOLD);
    mvprintw(AVG_WIN_Y(screen) - 6, AVG_WIN_X(screen) - 7, "JUST EXPLODE");
    attroff(A_BOLD);
    
    Menu *menu = menu_initialize
    (
        0, true, 4,
        variant_new("Size", 5, 1, "8x8", "10x10", "10x14", "14x18", "16x16"),
        variant_new("Difficulty", 3, 1, "Easy", "Normal", "Hard"),
        variant_new("Play!", 0, 0),
        variant_new("Back to main menu", 0, 0)
    );

    for (;;)
    {
        for (size_t i = 0, off = NEG(menu->q_variants / 2); i < menu->q_variants; ++i, ++off)
        {
            if (i == 2)
                off++;
            else if (i == 3)
                off += 3;

            if (i == 1 || i == 0)
            {
                move(AVG_WIN_Y(screen) + off, 0);
                clrtoeol();
            }

            if (i == menu->selected)
                attron(A_BOLD);

            char *choice = variant_display(menu_get_variant(menu, i));
            mvprintw(AVG_WIN_Y(screen) + off, CENTRE_STR(screen, choice), "%s", choice);
            free(choice);

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
            
            case KEY_LEFT:
            case 'a':
            case 'A':
                variant_select_prev(menu_get_variant_ptr(menu, menu->selected));
                break;

            case KEY_RIGHT:
            case 'd':
            case 'D':
                variant_select_next(menu_get_variant_ptr(menu, menu->selected));
                break;

            case KEY_ENTER:
            case 10: 
            {
                SetupGameMenu sel = (SetupGameMenu)menu->selected;
                if (sel < 2)
                    break;

                settings_setup(sett,
                                (FieldSize)menu->variants[0].selected_value,
                                (Difficulty)menu->variants[1].selected_value);
                menu_deinitialize(menu);
                return sel;
            }
        }

        refresh();
    }
}


void
screen_render_game(Screen *screen, Field *field)
{
    clear();

    static size_t sel_row = 0, sel_col = 0;
    
    const int   x_start = AVG_WIN_X(screen) - (4 * field->cols +1) / 2 -1,
                y_start = AVG_WIN_Y(screen) - (2 * field->rows +1) / 2 -1;
    
    
    attron(A_BOLD);
    mvprintw(y_start -5, AVG_WIN_X(screen) - 6, "JUST EXPLODE");
    attroff(A_BOLD);
    
    
    for (;;)
    {
        
        for (size_t i = 0; i < field->rows; ++i)
        {
            for (size_t j = 0; j < field->cols; ++j)
            {
                if ((i == sel_row && j == sel_col) || (i == sel_row && j == sel_col +1) || (i == sel_row +1 && j == sel_col) || (i == sel_row +1 && j == sel_col +1))
                    attron(A_BOLD);

                mvprintw
                (
                    i*2+0 + y_start, j*4 + x_start,
                    "+"
                );

                if ((i == sel_row +1 && j == sel_col +1) || (i == sel_row && j == sel_col +1))
                    attroff(A_BOLD);
                printw("---+");

                if (i == sel_row +1 && j == sel_col)
                    attroff(A_BOLD);
                if (i == sel_row && j == sel_col +1)
                    attron(A_BOLD);

                mvprintw
                (
                    i*2+1 + y_start, j*4 + x_start,
                    "|"
                );
                if (i == sel_row && j == sel_col +1)
                    attroff(A_BOLD);
                printw(" %d |", field->cells[i][j]);

                if (i == sel_row && j == sel_col +1)
                    attron(A_BOLD);
                mvprintw
                (
                    i*2+2 + y_start, j*4 + x_start,
                    "+"
                );
                if (i == sel_row && j == sel_col +1)
                    attroff(A_BOLD);
                printw("---+");

                attroff(A_BOLD);
            }
        }
        
        switch (wgetch(stdscr))
        {
            case KEY_DOWN:
            case 's':
            case 'S':
                sel_row = sel_row == field->rows -1 ? 0 : sel_row +1;
                break;
            
            case KEY_UP:
            case 'w':
            case 'W':
                sel_row = sel_row == 0 ? field->rows -1 : sel_row -1;
                break;
            
            case KEY_LEFT:
            case 'a':
            case 'A':
                sel_col = sel_col == 0 ? field->cols -1 : sel_col -1;
                break;

            case KEY_RIGHT:
            case 'd':
            case 'D':
                sel_col = sel_col == field->cols -1 ? 0 : sel_col +1;
                break;

            case KEY_ENTER:
            case 10: 
            {
            }
        }

        refresh();
    }
}
