#include "jmenu.h"

#include "stdarg.h"
#include "stdlib.h"


Menu *
menu_initialize(size_t default_sel, bool looped, size_t q_choices, ...)
{
    Menu *menu = (Menu *)malloc(sizeof(Menu));
    menu->selected = default_sel;
    menu->looped = looped;
    menu->q_choices = q_choices;

    menu->choises = (char **)malloc(sizeof(char *) * q_choices);

    va_list choices;
    va_start(choices, q_choices);

    for (size_t i = 0; i < q_choices; ++i)
    {
        menu->choises[i] = va_arg(choices, char *);
    }

    va_end(choices);
    return menu;
}

void
menu_deinitialize(Menu *menu)
{
    free(menu->choises);
    free(menu);
}
