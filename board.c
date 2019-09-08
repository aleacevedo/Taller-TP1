#include "board.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

int board_init(board_t *self) {
  FILE *fileBoard = fopen(PATH_BOARD, "r");
  int row = 0;
  char line[LEN_STRING + 2];
  if (fileBoard == NULL) {
    printf("Error initializing board: %s\n", strerror(errno));
    return 1;
  }
  while (fgets(line, LEN_STRING + 1, fileBoard) != NULL) {
    if (!(row < BOARD_SIZE)) {
      printf(" Error initializing board: The file is bigger than 9 rows");
      fclose(fileBoard);
      return 1;
    }
    for (int column = 0; column < BOARD_SIZE; column++) {
      if (line[column] == '0') {
        self->cells[row][column].value = ' ';
        self->cells[row][column].ini = 0;
        continue;
      }
      self->cells[row][column].value = line[column];
      self->cells[row][column].ini = 1;
    }
    row++;
  }
  return fclose(fileBoard);
}

int board_set(board_t *self, int row, int column, char value) {
  self->cells[row][column].value = value;
  return 0;
}

int board_is_ini(board_t *self, int row, int column) {
  return self->cells[row][column].ini;
}

char board_get(board_t *self, int row, int column) {
  return self->cells[row][column].value;
}

int board_reset(board_t *self) {
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int column = 0; column < BOARD_SIZE; column++) {
      if (!board_is_ini(self, row, column)) {
        board_set(self, row, column, ' ');
      }
    }
  }
  return 0;
}
