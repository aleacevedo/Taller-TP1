#include "sudoku.h"
#include <stdio.h>
#include <string.h>
#include "board.h"

int sudoku_init(sudoku_t *self)
{
  return board_init(&(self->board));
}

char *sudoku_show(sudoku_t *self, char *boardRepresentation) {
  for (int row = 0; row < 9; row++) {
    if (row % 3 == 0) {
      snprintf(boardRepresentation + strlen(boardRepresentation), BOARD_REPRESENTATION_LEN - strlen(boardRepresentation), "%s", SECTOR_DIVISOR);
    } else {
      snprintf(boardRepresentation + strlen(boardRepresentation), BOARD_REPRESENTATION_LEN - strlen(boardRepresentation), "%s", ROW_DIVISOR);
    }
    for (int column = 0; column < 9; column = column + 3) {
      char valor0 = board_get(&(self->board), row, column);
      char valor1 = board_get(&(self->board), row, column + 1);
      char valor2 = board_get(&(self->board), row, column + 2);
      snprintf(boardRepresentation + strlen(boardRepresentation), BOARD_REPRESENTATION_LEN - strlen(boardRepresentation), CELL_REPRESENTATION, valor0, valor1, valor2);
    }
    snprintf(boardRepresentation + strlen(boardRepresentation), BOARD_REPRESENTATION_LEN - strlen(boardRepresentation), "%s", "U\n");
  }
  snprintf(boardRepresentation + strlen(boardRepresentation), BOARD_REPRESENTATION_LEN - strlen(boardRepresentation), "%s", SECTOR_DIVISOR);
  return boardRepresentation;
}

int sudoku_set(sudoku_t *self, int row, int column, int value) {
  return 0;
}

int sudoku_validate(sudoku_t *self) {
  return 0;
}

int sudoku_reset(sudoku_t *self) {
  return 0;
}
