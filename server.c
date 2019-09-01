#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include "board.h"

void server_init(const char *service) {
  char boardRepresentation[BOARD_REPRESENTATION_LEN] = "\0";
  sudoku_t sudoku;
  board_t board;
  sudoku.board = &board;
  sudoku_init(&sudoku);
  printf("Levanto un server en el puerto: %s \n", service);
  sudoku_show(&sudoku, boardRepresentation);
  printf("%s \n", boardRepresentation);
  sudoku_set(&sudoku, '1','1','5');
  boardRepresentation[0] = '\0';
  sudoku_show(&sudoku, boardRepresentation);
  printf("%s \n", boardRepresentation);
  sudoku_set(&sudoku, '1','1','0');
  boardRepresentation[0] = '\0';
  sudoku_show(&sudoku, boardRepresentation);
  printf("%s \n", boardRepresentation);
  sudoku_reset(&sudoku);
  boardRepresentation[0] = '\0';
  sudoku_show(&sudoku, boardRepresentation);
  printf("%s \n", boardRepresentation);
  sudoku_uninit(&sudoku);
}
