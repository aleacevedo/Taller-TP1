#ifndef _BOARD_H
#define _BOARD_H

#define PATH_BOARD "./board.txt"
#define LEN_STRING 10
#define BOARD_SIZE 9

typedef struct {
  char value;
  int ini;
} cell_t;

typedef struct {
  cell_t cells[9][9];
} board_t;

int board_init(board_t *self);

int board_set(board_t *self, int row, int column, char value);

int board_is_ini(board_t *self, int row, int column);

char board_get(board_t *self, int row, int column);

int board_reset(board_t *self);

#endif
