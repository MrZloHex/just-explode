#pragma once

class Algorithm {
    private:
        // amount of cell; field is always square
        short size_field;
        // size of one cell in pexels
        short size_cell;
        // game field with all bombs
        unsigned short field[0xC][0xC];
        // game field which player sees
        unsigned short show_field[0xC][0xC];
        // amount of bombs on field
        //short amount_bomb = 0;

    public:
        // constructor of class; size_field, size_cell
        Algorithm(short sf, short sc);
        /* initing fields; field - generate bombs and nothing
                           show_field - all idk             */
        void init_fields();
        // places all markdowns at field
        void generate_map();
        // checking for explodes
        void bomb_handler();
        /* getting type of cell in field
            true - field
            false - show_field          */
        unsigned short get_type_of_cell(bool map, short x, short y);
        short get_size_field();
        short get_size_cell();
};