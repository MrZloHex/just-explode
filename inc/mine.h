#ifndef __MINE_H__
#define __MINE_H__

#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

#include "vec.h"
#include "settings.h"


const static int k_difficulty_multiplier[Q_DIFS] = { 9, 5, 2 };

typedef enum Cell_E
{
	Empty,
	Mine,
} Cell;

typedef enum PlayerCell_E
{
	EMPTY  = 0,
	MINE_1 = 1,
	MINE_2 = 2,
	MINE_3 = 3,
	MINE_4 = 4,
	MINE_5 = 5,
	MINE_6 = 6,
	MINE_7 = 7,
	MINE_8 = 8,
	FLAGGED,
	HIDDEN,
	EXPLODED_MINE
} PlayerCell;

typedef struct Field_S
{
	Cell **minefield;
	PlayerCell **playerfield;
	size_t rows;
	size_t cols;
	size_t q_mines;
	size_t q_flags;
} Field;


Field *
field_initialization(size_t rows, size_t cols);

Field *
field_initialize(SizePair size);

void
field_deinitilize(Field *field);

void
field_generate(Field *field, Difficulty diff, size_t row, size_t col);

Cell
field_get_cell(Field *field, size_t row, size_t col);

bool
_field_safe_get_cell(Field *field, size_t row, size_t col, Cell *cell);

void
field_set_cell(Field *field, size_t row, size_t col, Cell cell);

size_t
_field_count_mines(Field *field, size_t row, size_t col);

char
field_get_char_cell(Field *field, size_t row, size_t col);

void
field_set_flag(Field *field, size_t row, size_t col);

bool
field_reveal_playercell(Field *field, size_t row, size_t col);

bool
field_check_win(Field *field);

#endif /* __MINE_H__ */
