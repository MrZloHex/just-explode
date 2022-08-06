#include "jmenu.h"

#include "stdarg.h"
#include "stdlib.h"
#include "string.h"

Variant
variant_new(const char *name, size_t q_values, size_t def_sel, ...)
{
    Variant var = {0};
    var.name = name;
    var.selected_value = def_sel;
    var.q_values = q_values;
    
    if (var.q_values != 0)
    {
        va_list values;
        va_start(values, def_sel);

        var.values = (char **)malloc(sizeof(char *) * q_values);

        for (size_t i = 0; i < q_values; ++i)
        {
            var.values[i] = va_arg(values, char *);
        }

        va_end(values);
    }
    else
    {
        var.values = NULL;
    }

    return var;
}

void
variant_kill(Variant var)
{
    free(var.values);
}

char *
variant_display(Variant var)
{
    char *string = NULL;

    if (var.q_values != 0)
    {
        string = (char *)malloc(sizeof(char) * (strlen(var.name) + strlen(var.values[var.selected_value]) + 6 + 1));
        strcpy(string, var.name);
        if (var.selected_value == 0)
            strcat(string, ":   ");
        else
            strcat(string, ": < ");
        strcat(string, var.values[var.selected_value]);
        if (var.selected_value == var.q_values -1)
            strcat(string, "  ");
        else
            strcat(string, " >");
    }
    else
    {
        string = (char *)malloc(sizeof(char) * strlen(var.name) + 1);
        strcpy(string, var.name);
    }

    return string;
}



Menu *
menu_initialize(size_t default_sel, bool looped, size_t q_vars, ...)
{
    Menu *menu = (Menu *)malloc(sizeof(Menu));
    menu->selected = default_sel;
    menu->looped = looped;
    menu->q_variants= q_vars;

    menu->variants= (Variant *)malloc(sizeof(Variant) * q_vars);

    va_list choices;
    va_start(choices, q_vars);

    for (size_t i = 0; i < q_vars; ++i)
    {
        menu->variants[i] = va_arg(choices, Variant);
    }

    va_end(choices);
    return menu;
}

void
menu_deinitialize(Menu *menu)
{
    for (size_t i = 0; i < menu->q_variants; ++i)
        variant_kill(menu->variants[i]);

    free(menu->variants);
    free(menu);
}


Variant
menu_get_variant(Menu *menu, size_t sel)
{
    return menu->variants[sel];
}

Variant *
menu_get_variant_ptr(Menu *menu, size_t sel)
{
    return &menu->variants[sel];
}