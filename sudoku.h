#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "board.h"

#define SECTOR_DIVISOR "U===========U===========U===========U\n"
#define ROW_DIVISOR "U---+---+---U---+---+---U---+---+---U\n"
#define BOARD_REPRESENTATION_LEN 722
#define CELL_REPRESENTATION "U %c | %c | %c "

typedef struct
{
  board_t board;
  int valid;
} sudoku_t;

int sudoku_init(sudoku_t *self);

int sudoku_set(sudoku_t *self, int row, int column, int value);

char *sudoku_show(sudoku_t *self, char *boardRepresentation);

int sudoku_validate(sudoku_t *self);

int sudoku_reset(sudoku_t *self);

#endif
