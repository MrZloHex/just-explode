#include "mine.h"

#include <time.h>


Field *
field_initialization(size_t rows, size_t cols)
{
	srand(time(NULL));

	Field *field = (Field *)malloc(sizeof(Field));
	field->rows = rows;
	field->cols = cols;
	field->cells = (Cell **)malloc(sizeof(Cell *) * rows);
	for (size_t i = 0; i < rows; ++i)
	{
		field->cells[i] = (Cell *)malloc(sizeof(Cell) * cols);
		for (size_t j = 0; j < cols; ++j)
		{
			field->cells[i][j] = Empty;
		}
	}
	return field;
}

Field *
field_initialize(SizePair size)
{
	return field_initialization(size.x, size.y);	
}

void
field_generate(Field *field, Difficulty diff)
{
	for (size_t i = 0; i < field->rows; ++i)
	{
		for (size_t j = 0; j < field->cols; ++j)
		{
			if (rand() % (2 * k_difficulty_multiplier[diff]) == 1)
			{
				field->cells[i][j] = Mine;
			}
		}
	}
}

Cell
field_get_cell(Field *field, size_t row, size_t col)
{
	return field->cells[row][col];
}

bool
field_safe_get_cell(Field *field, size_t row, size_t col, Cell *cell)
{
	if (row >= 0 && row < field->rows && col >= 0 && col < field->cols)
	{
		*cell = field->cells[row][col];
		return true;
	}
	else
	{
		return false;
	}
}

void
field_set_cell(Field *field, size_t row, size_t col, Cell cell)
{
	field->cells[row][col] = cell;
}

size_t
_field_count_mines(Field *field, size_t row, size_t col)
{
	size_t mines = 0;
	Cell *cell = (Cell *)malloc(sizeof(Cell));
	for (int8_t i = -1; i < 2; ++i)
	{
		for (int8_t j = -1; j < 2; ++j)
		{
			if (i != 0 || j != 0)
			{
				if (field_safe_get_cell(field, row+i, col+j, cell))
				{
					if (*cell == Mine)
					{
						mines++;
					}
				}
			}
		}
	}
	free(cell);
	return mines;
}

void
field_print(Field *field)
{
	putchar('|');
	for (size_t j = 0; j < field->cols; ++j)
		printf("-|");
	putchar('\n');
	
	
	for (size_t i = 0; i < field->rows; ++i)
	{
		putchar('|');
		for (size_t j = 0; j < field->cols; ++j)
		{
			if (field_get_cell(field, i, j) == Empty)
			{
				size_t neigh = _field_count_mines(field, i, j);
				putchar( neigh == 0 ? ' ' : neigh + '0');
			}
			else
			{
				putchar('*');
			}
			putchar('|');
		}
		printf("\n|");
		for (size_t j = 0; j < field->cols; ++j)
			printf("-|");
		putchar('\n');
	}
}
