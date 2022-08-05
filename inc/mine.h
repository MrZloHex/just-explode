#ifndef __MINE_H__
#define __MINE_H__

#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

typedef enum Cell_E
{
	Empty,
	Mine
} Cell;

typedef struct Field_S
{
	Cell **cells;
	size_t rows;
	size_t cols;
} Field;


Field *
field_initialization(size_t rows, size_t cols);

Cell
field_get_cell(Field *field, size_t row, size_t col);

bool
field_safe_get_cell(Field *field, size_t row, size_t col, Cell *cell);

void
field_set_cell(Field *field, size_t row, size_t col, Cell cell);

size_t
_field_count_mines(Field *field, size_t row, size_t col);

void
field_print(Field *field);


#endif /* __MINE_H__ */
