#include "server.h"
#include <stdio.h>
#include "sudoku.h"
#include "board.h"

void server_init(const char *service)
{
  char boardRepresentation[BOARD_REPRESENTATION_LEN] = "\0";
  sudoku_t sudoku;
  sudoku_init(&sudoku);
  sudoku_show(&sudoku, boardRepresentation);
  printf("Levanto un server en el puerto: %s \n", service);
  printf("%s \n", boardRepresentation);
}
