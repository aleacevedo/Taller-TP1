#include "sudoku.h"
#include "board.h"

int sudoku_init(sudoku_t self) {
  return board_init(self->board)
}

char* sudoku_show(sudoku_t self) {
  char[BOARD_REPRESENTATION_LEN] boardRepresentation = "\0"
  for (int row = 0; row < 9; row++) {
    if (row % 3 == 0) {
      snprintf(board, BOARD_REPRESENTATION_LEN, "%s%s", board, SECTOR_DIVISOR);
    } else {
      snprintf(board, BOARD_REPRESENTATION_LEN, "%s%s", board, ROW_DIVISOR);
    }
    for (int column = 0; column < 9; column++) {
      snprintf(board, "")
    }
  }
}
