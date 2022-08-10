#include "mine.h"

#include <time.h>


Field *
field_initialization(size_t rows, size_t cols)
{
	srand(time(NULL));

	Field *field = (Field *)malloc(sizeof(Field));
	field->q_flags = 0;
	field->q_mines = 0;
	field->rows = rows;
	field->cols = cols;
	field->minefield = (Cell **)malloc(sizeof(Cell *) * rows);
	field->playerfield = (PlayerCell **)malloc(sizeof(PlayerCell *) * rows);
	for (size_t i = 0; i < rows; ++i)
	{
		field->minefield[i] = (Cell *)malloc(sizeof(Cell) * cols);
		field->playerfield[i] = (PlayerCell *)malloc(sizeof(PlayerCell) * cols);
		for (size_t j = 0; j < cols; ++j)
		{
			field->minefield[i][j] = Empty;
			field->playerfield[i][j] = HIDDEN;
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
field_deinitilize(Field *field)
{
	for (size_t i = 0; i < field->rows; ++i)
	{
		free(field->minefield[i]);
		free(field->playerfield[i]);
	}

	free(field->minefield);
	free(field->playerfield);
	free(field);
}

void
field_generate(Field *field, Difficulty diff, size_t row, size_t col)
{
	for (size_t i = 0; i < field->rows; ++i)
	{
		for (size_t j = 0; j < field->cols; ++j)
		{
			if (rand() % (2 * k_difficulty_multiplier[diff]) == 1)
			{
				field->minefield[i][j] = Mine;
				field->q_mines++;
			}
		}
	}
	if (field->minefield[row][col] == Mine)
	{
		field->minefield[row][col] = Empty;
		field->q_mines--;
	}
}

Cell
field_get_cell(Field *field, size_t row, size_t col)
{
	return field->minefield[row][col];
}

bool
_field_safe_get_cell(Field *field, size_t row, size_t col, Cell *cell)
{
	if (row >= 0 && row < field->rows && col >= 0 && col < field->cols)
	{
		*cell = field->minefield[row][col];
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
	field->minefield[row][col] = cell;
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
				if (_field_safe_get_cell(field, row+i, col+j, cell))
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

char
field_get_char_cell(Field *field, size_t row, size_t col)
{
	PlayerCell cell = field->playerfield[row][col];
	if (cell == HIDDEN)
		return ' ';
	else if (cell == FLAGGED)
		return '!';
	else if (cell == EXPLODED_MINE)
		return '*';
	else
		return cell + '0';
	return '?';
}

void
field_set_flag(Field *field, size_t row, size_t col)
{
	field->playerfield[row][col] = FLAGGED;
	field->q_flags++;
}

bool
field_reveal_playercell(Field *field, size_t row, size_t col)
{
	if (field->playerfield[row][col] == FLAGGED)
	{
		field->playerfield[row][col] = HIDDEN;
		field->q_flags--;
	}
	else
	{
		if (field->minefield[row][col] == Mine)
		{
			field->playerfield[row][col] = EXPLODED_MINE;
			return true;
		}
		else
		{
			field->playerfield[row][col] = (PlayerCell)_field_count_mines(field, row, col);
		}
	}
	return false;
}

bool
field_check_win(Field *field)
{
	if (field->q_flags == field->q_mines)
	{
		for (size_t i = 0; i < field->rows; ++i)
			for (size_t j = 0; j < field->cols; ++j)
				if ((field->minefield[i][j] == Mine && field->playerfield[i][j] != FLAGGED) || field->playerfield[i][j] == HIDDEN)
					return false;

		return true;
	}
	else
	{
		return false;
	}
}
