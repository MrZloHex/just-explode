#ifndef __JMENU_H__
#define __JMENU_H__

#include "stddef.h"
#include "stdbool.h"

typedef struct Menu_S
{
    char **choises;
    size_t q_choices;
    size_t selected;
    bool looped;
} Menu;

Menu *
menu_initialize(size_t default_sel, bool looped, size_t q_choices, ...);

static inline void
menu_select_next(Menu *menu)
{
    if (menu->selected == menu->q_choices -1)
        menu->selected = menu->looped ? 0 : menu->selected;
    else
        menu->selected++;
}

static inline void
menu_select_prev(Menu *menu)
{
    if (menu->selected == 0)
        menu->selected = menu->looped ? menu->q_choices -1 : 0;
    else
        menu->selected--;
}

void
menu_deinitialize(Menu *menu);

#endif /* __JMENU_H__ */