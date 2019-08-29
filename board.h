#ifndef _BOARD_H
#define _BOARD_H

#define PATH_BOARD "./board.txt"
#define LEN_STRING 9

typedef struct {
  char value = " ";
  boolean ini = false;
  boolean empty = true;
} cell_t

typedef cell_t board_t[9][9]

int board_init(board_t* self);

int board_set(board_t* self, int row, int column, int value);

int board_get(board_t* self, int row, int column)

int board_reset(board_t* self);

#endif
