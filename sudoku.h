#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "board.h"
#include "list.h"

#define SECTOR_DIVISOR "U===========U===========U===========U\n"
#define ROW_DIVISOR "U---+---+---U---+---+---U---+---+---U\n"
#define BOARD_REPRESENTATION_LEN 722
#define ROW_REPRESENTATION "U %c | %c | %c "

typedef struct {
  board_t *board;
  list_t *plays;
} sudoku_t;

typedef struct {
  int row;
  int column;
  char value;
} play_t;

int sudoku_init(sudoku_t *self);

int sudoku_set(sudoku_t *self, char row, char column, char value);

char *sudoku_show(sudoku_t *self, char *boardRepresentation);

int sudoku_validate(sudoku_t *self);

int sudoku_reset(sudoku_t *self);

void sudoku_uninit(sudoku_t *self);

#endif
