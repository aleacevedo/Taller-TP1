#include "server.h"
#include <stdio.h>
#include "sudoku.h"

void server_init(const char* service) {
  sudoku_t sudoku;
  sudoku_init(sudoku);
  printf("Levanto un server en el puerto: %s \n", service);
}
