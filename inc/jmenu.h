#ifndef __JMENU_H__
#define __JMENU_H__

#include "stddef.h"
#include "stdbool.h"

typedef struct Variant_S
{
    size_t q_values;
    const char *name;

    size_t selected_value;
    char **values;
} Variant;

Variant
variant_new(const char *name, size_t q_values, size_t def_sel, ...);

void
variant_kill(Variant var);

char *
variant_display(Variant var);

static inline void
variant_select_next(Variant *var)
{
    if (var->q_values == 0) return;
    var->selected_value = var->selected_value == var->q_values -1 ? var->selected_value : var->selected_value + 1;
}

static inline void
variant_select_prev(Variant *var)
{
    if (var->q_values == 0) return;
    var->selected_value = var->selected_value == 0 ? var->selected_value : var->selected_value - 1;
}


typedef struct Menu_S
{
    Variant *variants;
    size_t q_variants;
    size_t selected;
    bool looped;
} Menu;

Menu *
menu_initialize(size_t default_sel, bool looped, size_t q_vars, ...);

static inline void
menu_select_next(Menu *menu)
{
    if (menu->selected == menu->q_variants -1)
        menu->selected = menu->looped ? 0 : menu->selected;
    else
        menu->selected++;
}

static inline void
menu_select_prev(Menu *menu)
{
    if (menu->selected == 0)
        menu->selected = menu->looped ? menu->q_variants -1 : 0;
    else
        menu->selected--;
}

Variant
menu_get_variant(Menu *menu, size_t sel);

Variant *
menu_get_variant_ptr(Menu *menu, size_t sel);

void
menu_deinitialize(Menu *menu);

#endif /* __JMENU_H__ */