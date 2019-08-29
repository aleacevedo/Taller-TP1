#include "board.h"

#include <stdio.h>

int board_init(board_t* self) {
  FILE *fileBoard = fopen(PATH_BOARD);
  int row = 0;
  char line[LEN_STRING+1];
  if (fileBoard == NULL) return -2;
  while (!feof(fileBoard)) {
    fgets(line, LEN_STRING+1, fileBoar);
    if (row > 8) {
      fclose(fileBoard);
      return -1;  // El archivo tiene mas de 9 filas
    }
    for (int column = 0; column < 9; clumn++) {
      if (line[column] == 0) continue;
      board[row][column]->value = line[column];
      board[row][column]->ini = true;
      board[row][column]->empty = false;
    }
  }
  return fclose(fileBoard)
}
